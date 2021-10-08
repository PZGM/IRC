#ifndef SERVER_HPP
# define SERVER_HPP

# include <sys/socket.h>
# include <sys/types.h>
# include <sys/time.h>
# include <netinet/in.h>
# include <iostream>
# include <cstring>
# include <unistd.h>
# include <sys/poll.h>
# include <poll.h>
# include <arpa/inet.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <fcntl.h>
# include <vector>
# include <list>
# include <map>
# include "User.hpp"
# include "Channel.hpp"
# include "Class_server.hpp"



#define PORT 8080
#define BUFF 1024
#define BACKLOG 7
#define FD_MAX 2000

using namespace std;



// SERVER.HPP
int initialize_socket_fd();
void init_address(struct sockaddr_in * addr, int sockfd);




// PARSING.CPP
vector<string> * split(string str, string sep);
void parsing(std::string str, User & usr);


// JOIN.CPP
void join(vector<string> *vec, User & usr);

// NICK.CPP
void nick(vector<string> *vec, User & usr);

// USER.CPP
void user(vector<string> *vec, User & usr);

// TOOL.CPP
string allupper(string str);


#endif