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
# include <fstream>
# include <errno.h>
# include <fcntl.h>
# include <vector>
# include <list>
# include <map>
# include "User.hpp"
# include "Channel.hpp"
# include "Class_server.hpp"
# include <ctime>


#define PORT 8080
#define BUFF 1024
#define BACKLOG 7
#define FD_MAX 2000
#define SERVER_NAME "mepd"
#define SERVER_VERSION "0.0.1"

using namespace std; //VIRER TOUT LES STD



// SERVER.HPP
int initialize_socket_fd();
void init_address(struct sockaddr_in * addr, int sockfd, int port);
bool file_exist(const char *file);

// PARSING.CPP
vector<string> * split(string str, string sep);
void parsing(std::string str, User & usr, Server & srv);

// JOIN.CPP
void join(vector<string> *vec, User & usr, Server & srv);

// NICK.CPP
void nick(vector<string> *vec, User & usr, Server & srv);

// USER.CPP
void user(vector<string> *vec, User & usr, Server & srv);

// PRIVMSG.CPP
void privmsg(vector<string> *vec, User & usr, Server & srv);
bool	privmsg_user(vector<string> *vec, User & usr, Server & srv);
bool	privmsg_channel(vector<string> *vec, User & usr, Server & srv);

// OPER.CPP
void oper(vector<string> *vec, User & usr, Server & srv);

// MODE.CPP
void mode(vector<string> *vec, User & usr, Server & srv);

// MODE_CHAN
void mode_chan(vector<string> *vec, User & usr, Server & srv);

// TOOL.CPP
string allupper(string str);
bool	close_connection(int i, struct pollfd &fds, map<int, User> & users, Server & srv);

//UTILS.CPP
void send(std::string str, int fd);
void send_error(int err, User & usr);
void send_error(int err, User & usr, std::string ctx);
void send_rpl(int rpl, User & usr);
void send_rpl(int rpl, User & usr, string s1);
void send_rpl(int rpl, User & usr, string s1, string s2);
void send_update(User & usr, string command, string params);
void send_update(User & usr, Server & srv, string command, string params);
void broadcast_update(User & usr, Server & srv, string command, string params);
bool check_nick(std::string str);
bool check_nick_availibility(std::string str, Server & srv);
bool check_user_name(std::string str);
map<int, string> get_msgs(void);
string prefix(int num);
void send_msg(string msg, User &usr);
void send_msg2(int num, User & usr, string msg);
void send_privmsg(User & usr, Server & srv, string command, string params, int fd);

//REGISTRATION.CPP
bool register_user(User & usr, Server & srv);

//PONG.CPP
void ping(vector<string> *vec, User & usr, Server & srv);
void pong(vector<string> *vec, User & usr, Server & srv);

//MODE_CHANS_CPP
void mode_chan(vector<string> *vec, User & usr, Server & srv);

//CONF.CPP
Server	configure(char *path);

#endif
