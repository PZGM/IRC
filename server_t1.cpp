#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>

#define PORT 8080
#define BUFF 1024
#define BACKLOG 4

void chat(int sockfd)
{
	char buff[BUFF];
	int n;
	while(1) {
		bzero(buff, BUFF);

		read(sockfd, buff, sizeof(buff));
		std::cout<<"From client: "<< buff<<std::endl<< "To client : ";
		bzero(buff, BUFF);
		n = 0;
		// copy server message in the buffer
		while ((buff[n++] = getchar()) != '\n')
			;
		// and send that buffer to client
		write(sockfd, buff, sizeof(buff));
		if (strncmp("exit", buff, 4) == 0) {
			printf("Server Exit...\n");
			break;
		}
	}
}

int main(int argc,char **argv) {

	char buff[BUFF] = {0};
	struct sockaddr_in addr;
	struct timeval	time;

	int connfd, val, rc, max_sd, new_sd, desc, end_serv, close_conn, len;
	int opt = 1;
	int addrlen = sizeof(addr);
	fd_set	master_set, curr_set;

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPV4(AF_INET6...) SOCK_STREAM = TCP 0 = IP
	if (sockfd == -1) { //execption instead of if ?
		std::cerr <<"socket creation failed" <<std::endl;
		exit(0);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR |SO_REUSEPORT, &opt, sizeof(opt))){ //to prevent error such as "address already in use
		std::cerr << "setsockopt error" << std::endl;
		exit(0);
	}

	if ((rc = ioctl(sockfd, FIONBIO, &opt, sizeof(opt))) < 0) { //set socket to be nonblocking
		std::cerr << "ioctl error" << std::endl;
		exit(0);
	}
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY; // all address accepted
	addr.sin_port = htons(PORT); //convert an integer from an byt of the server to on of the host

	if (bind(sockfd, (struct sockaddr *) &addr, addrlen) < 0) {
		std::cerr << "bind error" <<std::endl;
		exit(0);
	}

	if (listen(sockfd, BACKLOG ) < 0) {
		std::cerr << "error while listening" <<std::endl;
		exit(0);
	}

	FD_ZERO(&master_set); //set up of multi user (for select)
	max_sd = sockfd;
	FD_SET(sockfd, &master_set);

	time.tv_sec = 3 * 60; //set timeout time (not in the subject in think)
	time.tv_usec = 0;
	do
	{
		memcpy(&curr_set, &master_set, sizeof(master_set)); //copy master into the working fd set
		if ((rc = select(max_sd + 1, &curr_set, NULL, NULL, &time)) < 0) { //replace with poll
			std::cerr <<"select failure " << std::endl;
			break;
		}
		if (rc == 0) {
			std::cerr << "select time out... " << std::endl;
			break;
		}

		if ((connfd = accept(sockfd, (struct sockaddr *) &addr, (socklen_t*) &addrlen)) < 0) {
			std::cerr << " error while accepting " << std::endl;
			exit(0);
		}
		desc = rc;
		for ( int i = 0; i < max_sd && desc > 0; i++)
		{
			if (FD_ISSET(i , &curr_set)) //checking if the descriptor is ready
			{
				desc--;
				if (i == sockfd) {// checking if this is the listening socket
					std::cout << "listening socket is readable"<< std::endl;
					do {
						new_sd = accept(sockfd, NULL, NULL); //why NULL NULL ?
						if (new_sd < 0) {
							if (errno != EWOULDBLOCK) { // errror from all accepting
								std::cerr << "accept failure" << std::endl;
								end_serv = 1;
							}
							break;
						}
						std::cout << "new incoming connection - "<< new_sd << std::endl;
						FD_SET(new_sd, &master_set); //add the new connection to the master set
						if (new_sd > max_sd)
							max_sd = new_sd;
					} while(new_sd != -1);
				}
				else //not the listening socket so an existing connection must be readable
				{
					std::cout << " Descriptor " << i << " is readable " << std::endl;
					close_conn = 0;
					do {
						if ((rc = recv(i, buff, sizeof(buff), 0)) < 0) //receive data
						{
							if (errno != EWOULDBLOCK)
							{
								std::cerr << " recv error" << std::endl;
								close_conn = 1;
							}
							break;
						}
						if (rc == 0)
						{
							std::cout << "connection close " <<std::endl;
							close_conn = 1;
							break;
						}
						len = rc;
						std::cout << len << "bytes received " << std::endl;
						if ((rc = send(i, buff, len, 0)) < 0)
						{
							std::cerr << " send error " << std::endl;
							close_conn = 1;
							break;
						}
					} while(1);
					if (close_conn)
					{
						close(i);
						FD_CLR(i, &master_set);
						if (i == max_sd)
						{
							while (!(FD_ISSET(max_sd, &master_set)))
								max_sd--;
						}
					}
				}
			}
		}
	} while(!end_serv);
	for (int i = 0; i <= max_sd;i++)
	{
		if ( FD_ISSET(i, &master_set))
			close(i);
	}
	return 0;
}
