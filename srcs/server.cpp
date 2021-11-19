#include "../include/server.hpp"

int initialize_socket_fd()
{
	int opt = 1;
	int rc;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPV4(AF_INET6...) SOCK_STREAM = TCP 0 = IP
	if (sockfd == -1) { //execption instead of if ?
		std::cerr <<"socket creation failed" <<std::endl;
		exit(0);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){ //to prevent error like "address already in use
		std::cerr << "setsockopt error" << std::endl;
		perror("error :");
		exit(0);
	}
	if ((rc = fcntl(sockfd, F_SETFL, O_NONBLOCK)) < 0) //((rc = ioctl(sockfd, FIONBIO, &opt)) < 0)
	{													 //set socket to be nonblocking
		std::cerr << "fnctl error" << std::endl;
		exit(0);
	}
	return sockfd;
}

void init_address(struct sockaddr_in * addr, int sockfd, int port) {
	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr =  INADDR_ANY;//inet_addr("127.0.0.1");//INADDR_ANY; // all address accepted
	addr->sin_port = htons(port); //convert an integer from an byt of the server to on of the host

	if (bind(sockfd, (struct sockaddr *) addr, sizeof(*addr)) < 0) {
		std::cerr << "bind error" <<std::endl;
		exit(0);
	}

	if (listen(sockfd, BACKLOG ) < 0) {
		std::cerr << "error while listening" <<std::endl;
		exit(0);
	}
}

bool	check_users(int i, pollfd &fds, std::map<int, User> & users, Server & srv, std::map<int, std::string> & inputs)
{
	int fd = (&fds)[i].fd;
	bool close_conn = false;
	char buff[BUFF] = {0};
	do {
		memset(buff, 0, sizeof(buff)); 
		int rc = recv(fd, buff, sizeof(buff),  MSG_DONTWAIT); //receive data
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				// std::cerr << " recv error" << std::endl;
				close_conn = true;
			}
			return false;
		}
		if (rc == 0)
		{
			users.erase(users.find(fd));
			std::cout << "user deleted from database" << std::endl;
			close_conn = true;
			break;
		}
		inputs[fd] += buff;
		if (inputs[fd].find("\n") != std::string::npos) {
			User & usr = users[fd];
			std::vector<std::string> * vec = split(inputs[fd], "\n");
			std::vector<std::string>::iterator it = vec->begin();
			while (it != vec->end()){
				parsing(*it, usr, srv);
				it++;
			}
			inputs[fd] = "";
		}
	} while(true);
	if (close_conn)
	{
		close(fd);
		(&fds)[i].fd = -1;
		return true;
	}
	return false;
}

Server routine(Server srv, int sockfd, int *nfds) {
	
	int size,new_sd, rc, i;
	bool end_serv = false;
	bool compr_arr = false;
	struct sockaddr_in addr;
	char ip[16];
	socklen_t len = sizeof(addr);
	std::map<int, std::string> inputs;

	std::map<int, User> & users = srv.get_users();
	do
	{
		std::cout << " waiting poll..." << std::endl;
		if ((rc = poll(srv.get_fds(), *nfds, -1)) < 0)
		{
			std::cerr << "poll failed" << std::endl;
			break;
		}
		if (rc == 0) {
			std::cerr << "poll timed out..." << std::endl;
			break;
		}
		size = *nfds;					//with poll need to find which descriptor are readable	
		for (i = 0; i < size; i++) {
			if (srv.fds[i].revents == 0)
				continue;
			if (srv.fds[i].revents % 2 != POLLIN) //if != 0 && != POLLIN then its unexpected
			{
				perror("=====>");
				std::cout << "i = " << i << std::endl;
				std::cout <<" Error revents = " << srv.fds[i].revents << std::endl;
				std::cout << errno << std::endl;
				end_serv = true;
				break;
			}
			if (srv.fds[i].fd == sockfd)
			{
				std::cout << "Listening socket is readable"<< std::endl;
				do
				{
					new_sd = accept(sockfd, NULL, NULL);
					if (new_sd < 0) {
						if (errno != EWOULDBLOCK) { // errror from all accepting
							std::cerr << "accept failure" << std::endl;
							end_serv = true;
						}
						break;
					}
					std::cout << "new incoming connection - "<< new_sd << std::endl;
					srv.fds[*nfds].fd = new_sd;
					srv.fds[*nfds].events = POLLIN;
					if (users.find(new_sd) == users.end()) {
						bzero(&addr, sizeof(addr));
						getpeername(new_sd, (struct sockaddr *)&addr, &len);
					    strcpy(ip, inet_ntoa(addr.sin_addr));
						std::cout << "User " << new_sd << " creation" << std::endl;	
						users[new_sd] = User(new_sd, std::string(ip));
						inputs[new_sd] = "";
					}
					(*nfds)++;
				} while(new_sd != -1);
			}
			else //not the listening socket so an existing connection must be readable
				compr_arr = check_users(i, *(srv.get_fds()), users, srv, inputs);
		}

		if (compr_arr)
		{
			compr_arr = false;
			for ( int i = 0; i < *nfds; i++)
			{
				if (srv.fds[i].fd == -1)
				{
					for (int j = i; j < *nfds; j++)
						srv.fds[j].fd = srv.fds[j +1].fd;
					i--;
					(*nfds)--;
				}
			}
		}
	} while(end_serv == false);
	return srv;
}

// ===========================================================================================
// ./ircserv [host:port_network:password_network] <port> <password>
// ===========================================================================================
int main(int argc,char **argv) {

	if (argc < 2 || argc > 3) { //accepte que host password car on gere pas multi serv
		std::cout << "error wrong number of args" << std::endl;
		return 0;
	}

	struct sockaddr_in addr;
	int i, sockfd;
	// struct pollfd fds[FD_MAX];
	int nfds = 1;

	Server srv;
	if (argc == 3)
		srv = Server(argv[1], argv[2]);
	else
		srv = configure(argv[1]);
	sockfd = initialize_socket_fd();
	init_address(&addr, sockfd, srv.get_port());
	srv.set_fds(sockfd);
	srv = routine(srv, sockfd, &nfds);
	for (i = 0; i < nfds; i++)
	{
		if (srv.fds[i].fd >= 0)
			close(srv.fds[i].fd);
	}
	return 0;
}
