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
#define SERVER_NAME "mepd"

using namespace std;



// SERVER.HPP
int initialize_socket_fd();
void init_address(struct sockaddr_in * addr, int sockfd);


// PARSING.CPP
vector<string> * split(string str, string sep);
void parsing(std::string str, User & usr);


// JOIN.CPP
void join(vector<string> *vec, User & usr, Server & srv);

// NICK.CPP
void nick(vector<string> *vec, User & usr, Server & srv);

// USER.CPP
void user(vector<string> *vec, User & usr, Server & srv);

// PRIVMSG.CPP
void privmsg(vector<string> *vec, User & usr, Server & srv);

// OPER.CPP
void oper(vector<string> *vec, User & usr, Server & srv);

// MODE.CPP
void mode(vector<string> *vec, User & usr, Server & srv);

// TOOL.CPP
string allupper(string str);

//UTILS.CPP
void send(std::string str, int fd);
void send_error(int err, User & usr);
void send_error(int err, User & usr, std::string msg);
void send_update(User & usr, std::string command, std::string params);
bool check_nick(std::string str);





#endif