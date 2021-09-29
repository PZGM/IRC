#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/poll.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <errno.h>

#define PORT 8080
#define BUFF 1024
#define BACKLOG 4
#define FD_MAX 200

int main(int argc,char **argv) {

	char buff[BUFF] = {0};
	struct sockaddr_in addr;
	//struct timeval	time;
	int time;
	int connfd, val, rc, max_sd, new_sd, desc, len;
	int opt = 1;
	bool close_conn = true;
	bool end_serv = false;
	int addrlen = sizeof(addr);
	//	fd_set	master_set, curr_set;
	struct pollfd fds[FD_MAX];
	bool compr_arr = false;
	int nfds = 1;
	int size = 0;
	int i;

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

	/*	FD_ZERO(&master_set); //set up of multi user (for select)
		max_sd = sockfd;
		FD_SET(sockfd, &master_set);
		*/
	memset(fds,0, sizeof(fds));
	fds[0].fd = sockfd;
	fds[0].events = POLLIN;

/*	time.tv_sec = 3 * 60; //set timeout time (not in the subject in think)
	time.tv_usec = 0;
*/	time = ( 3 * 60 * 1000);
	do
	{
		/*		memcpy(&curr_set, &master_set, sizeof(master_set)); //copy master into the working fd set
				if ((rc = select(max_sd + 1, &curr_set, NULL, NULL, &time)) < 0) { //replace with poll
				std::cerr <<"select failure " << std::endl;
				break;
				}
				*/		std::cout << " waiting poll..." << std::endl;
		if ((rc = poll(fds, nfds, time)) < 0)
		{
			std::cerr << "poll failed" << std::endl;
			break;
		}
		if (rc == 0) {
			//	std::cerr << "select timed out... " << std::endl;
			std::cerr << "poll timed out..." << std::endl;
			break;
		}
		size = nfds;					//with poll need to find which descriptor are readable
		for (i = 0; i < size; i++)
		{
			if (fds[i].revents == 0)
				continue;
			if (fds[i].revents != POLLIN) //if != 0 && != POLLIN then its unexpected
			{
				std::cout <<" Error revents = " << fds[i].revents << std::endl;
				end_serv = true;
				break;
			}
			if (fds[i].fd == sockfd)
			{
				/*desc = rc;
				  for ( int i = 0; i < max_sd && desc > 0; i++)
				  {
				  if (FD_ISSET(i , &curr_set)) //checking if the descriptor is ready
				  {
				  desc--;
				  if (i == sockfd) {// checking if this is the listening socket
				  */					std::cout << "Listening socket is readable"<< std::endl;
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
					/*	FD_SET(new_sd, &master_set); //add the new connection to the master set
						if (new_sd > max_sd)
						max_sd = new_sd;*/
					fds[nfds].fd = new_sd;
					fds[nfds].events = POLLIN;
					nfds++;
				} while(new_sd != -1);
			}
				  else //not the listening socket so an existing connection must be readable
				  {
					  std::cout << " Descriptor " << i << " is readable " << std::endl;
					  close_conn = false;
					  do {
						  //	if ((rc = recv(i, buff, sizeof(buff), 0)) < 0) //receive data
						  if ((rc = recv(fds[i].fd, buff, sizeof(buff), 0)) < 0)
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
						  std::cout << len << "bytes received " << std::endl;
						  //	if ((rc = send(i, buff, len, 0)) < 0)
						  if ((rc = send(fds[i].fd, buff, len, 0)) < 0)
						  {
							  std::cerr << " send error " << std::endl;
							  close_conn = true;
							  break;
						  }
					  } while(true);
					  if (close_conn)
					  {
						  /*	close(i);
								FD_CLR(i, &master_set);
								if (i == max_sd)
								{
								while (!(FD_ISSET(max_sd, &master_set)))
								max_sd--;
								}
								*/
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
				/*	for (int i = 0; i <= max_sd;i++)
					{
					if ( FD_ISSET(i, &master_set))
					close(i);
					*/
				for (i = 0; i < nfds; i++)
				{
					if (fds[i].fd >= 0)
						close(fds[i].fd);
				}
				return 0;
			}
