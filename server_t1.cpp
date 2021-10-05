#include "server.hpp"




int initialize_socket_fd() {
	int opt = 1;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPV4(AF_INET6...) SOCK_STREAM = TCP 0 = IP
	if (sockfd == -1) { //execption instead of if ?
		std::cerr <<"socket creation failed" <<std::endl;
		exit(0);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0){ //to prevent error such as "address already in use
		std::cerr << "setsockopt error" << std::endl;
		perror("error :");
		exit(0);
	}
	return sockfd;
}

void init_address(struct sockaddr_in * addr, int sockfd) {
	memset(addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;
	addr->sin_addr.s_addr = inet_addr("127.0.0.1");//INADDR_ANY; // all address accepted
	addr->sin_port = htons(PORT); //convert an integer from an byt of the server to on of the host

	if (bind(sockfd, (struct sockaddr *) addr, sizeof(*addr)) < 0) {
		std::cerr << "bind error" <<std::endl;
		exit(0);
	}

	if (listen(sockfd, BACKLOG ) < 0) {
		std::cerr << "error while listening" <<std::endl;
		exit(0);
	}
}

int main(int argc,char **argv) {
	(void)argc;
	(void)argv;
	char buff[BUFF] = {0};
	struct sockaddr_in addr;
	int time;
	int connfd, val, rc, max_sd, new_sd, desc, len;

	bool close_conn = true;
	bool end_serv = false;
	int addrlen = sizeof(addr);
	struct pollfd fds[FD_MAX];
	bool compr_arr = false;
	int nfds = 1;
	int size = 0;
	int i;

	int sockfd = initialize_socket_fd();

	if ((rc = fcntl(sockfd, F_SETFL, O_NONBLOCK)) < 0) { //set socket to be nonblocking
		std::cerr << "fnctl error" << std::endl;
		exit(0);
	}

	init_address(&addr, sockfd);

		memset(fds,0, sizeof(fds));
	fds[0].fd = sockfd;
	fds[0].events = POLLIN;

	map<int, User> users = map<int, User>();

	time = ( 3 * 60 * 1000);
	do
	{
		std::cout << " waiting poll..." << std::endl;
		if ((rc = poll(fds, nfds, -1)) < 0)
		{
			std::cerr << "poll failed" << std::endl;
			break;
		}
		if (rc == 0) {
			std::cerr << "poll timed out..." << std::endl;
			break;
		}
		size = nfds;					//with poll need to find which descriptor are readable
		for (i = 0; i < size; i++) {
			if (users.find(i) == users.end()) {
				users[i] = User(i);
			}
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents % 2  != POLLIN) //if != 0 && != POLLIN then its unexpected
			{
				std::cout <<" Error revents = " << fds[i].revents << std::endl;
				std::cout << errno << std::endl;
				end_serv = true;
				break;
			}
			if (fds[i].fd == sockfd)
			{
				std::cout << "Listening socket is readable"<< std::endl;
				do
				{
					new_sd = accept(sockfd, NULL, NULL); //why NULL NULL ?
					if (new_sd < 0) {
						if (errno != EWOULDBLOCK) { // errror from all accepting
							std::cerr << "accept failure" << std::endl;
							end_serv = true;
						}
						break;
					}
					std::cout << "new incoming connection - "<< new_sd << std::endl;
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				} while(new_sd != -1);
			}
			else //not the listening socket so an existing connection must be readable
			{
				close_conn = false;
				do {
					memset(buff, 0, sizeof(buff)); 
					rc = recv(fds[i].fd, buff, sizeof(buff),  0); //receive data
					if (rc < 0)
					{
						if (errno != EWOULDBLOCK)
						{
							std::cerr << " recv error" << std::endl;
							close_conn = true;
						}
						break;
					}
					if (rc == 0)
					{
						std::cout << "connection close " <<std::endl;
						close_conn = true;
						break;
					}
					len = rc;

					std::string input(buff);
					parsing(input, users[i]);

					// std::cout << len << "bytes received " << std::endl;
					if ((rc = send(fds[i].fd, buff, len, 0)) < 0)
					{
						std::cerr << " send error " << std::endl;
						close_conn = true;
						break;
					}
				} while(true);
				if (close_conn)
				{
					close(fds[i].fd);
					fds[i].fd = -1;
					compr_arr = true;
				}
			}
		}
		if (compr_arr)
		{
			compr_arr = false;
			for ( int i = 0; i < nfds; i++)
			{
				if (fds[i].fd == -1)
				{
					for (int j = i; j < nfds; j++)
						fds[j].fd = fds[j +1].fd;
					i--;
					nfds--;
				}
			}
		}
	} while(end_serv == false);
	for (i = 0; i < nfds; i++)
	{
		if (fds[i].fd >= 0)
			close(fds[i].fd);
	}
	return 0;
}
