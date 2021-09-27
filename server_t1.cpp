#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>

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
	int connfd, val;
	char buf[BUFF] = {0};
	struct sockaddr_in addr;
	int opt = 1;
	int addrlen = sizeof(addr);

	int sockfd = socket(AF_INET, SOCK_STREAM, 0); //AF_INET = IPV4(AF_INET6...) SOCK_STREAM = TCP 0 = IP
	if (sockfd == -1) { //execption instead of if ?
		std::cerr <<"socket creation failed" <<std::endl;
		exit(0);
	}
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR |SO_REUSEPORT, &opt, sizeof(opt))){ //to prevent error such as "address already in use
		std::cerr << "setsockopt error" << std::endl;
		exit(0);
	}

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
	if ((connfd = accept(sockfd, (struct sockaddr *) &addr, (socklen_t*) &addrlen)) < 0) {
		std::cerr << " error while accepting " << std::endl;
		exit(0);
	}
	chat(connfd);
	close(sockfd);
	return 0;
}
