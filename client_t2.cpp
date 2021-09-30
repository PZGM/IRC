/**************************************************************************/
/* Generic client example is used with connection-oriented server designs */
/**************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

#define SERVER_PORT  8080

int main(int argc, char *argv[])
{
	int    len, rc;
	int    sockfd;
	char   send_buf[80];
	char   recv_buf[80];
	struct sockaddr_in   addr;

	/*************************************************/
	/* Create an AF_INET6 stream socket              */
	/*************************************************/
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("socket");
		exit(-1);
	}

	/*************************************************/
	/* Initialize the socket address structure       */
	/*************************************************/
	memset(&addr, 0, sizeof(addr));
	addr.sin_family      = AF_INET;
	addr.sin_addr.s_addr		= INADDR_ANY;
	addr.sin_port      = htons(SERVER_PORT);

	/*************************************************/
	/* Connect to the server                         */
	/*************************************************/
	rc = connect(sockfd,
			(struct sockaddr *)&addr,
			sizeof(struct sockaddr_in));
	if (rc < 0)
	{
		perror("error ");
		std::cerr<<"error while connecting"<<std::endl;
		close(sockfd);
		exit(-1);
	}
	std::cout << "Connect completed"<<std::endl;

	/*************************************************/
	/* Enter data buffer that is to be sent          */
	/*************************************************/
	std::cout << " Enter message to sent" << std::endl;
	fgets(send_buf, sizeof(send_buf), stdin);

	/*************************************************/
	/* Send data buffer to the worker job            */
	/*************************************************/
	len = send(sockfd, send_buf, strlen(send_buf) + 1, 0);
	if (len != strlen(send_buf) + 1)
	{
		std::cerr <<"send";
		close(sockfd);
		exit(-1);
	}
	std::cout << len << " bytes sent" << std::endl;

	/*************************************************/
	/* Receive data buffer from the worker job       */
	/*************************************************/
	len = recv(sockfd, recv_buf, sizeof(recv_buf), 0);
	std::cout << "recv = " << len << std::endl;
	if (len != strlen(send_buf) + 1)
	{
		std::cerr << "recv" << std::endl;
		close(sockfd);
		exit(-1);
	}
	std::cout << len << " bytes receive" << std::endl;
	/*************************************************/
	/* Close down the socket                         */
	/*************************************************/
	close(sockfd);
	return 0;
}
