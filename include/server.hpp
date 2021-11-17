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
#define SERVER_NAME "irc.mepd"
#define SERVER_VERSION "0.7.13"




// SERVER.HPP
int initialize_socket_fd(int *rc);
void init_address(struct sockaddr_in * addr, int sockfd, int port);
bool check_users(int i, struct pollfd &fds, std::map<int, User> & users, Server & srv);

// PARSING.CPP
std::vector<std::string> * split(std::string str, std::string sep);
void parsing(std::string str, User & usr, Server & srv);

// JOIN.CPP
void join(std::vector<std::string> *vec, User & usr, Server & srv);
void welcome_chan(User & usr, Server srv, Channel & chan);

// WHO.CPP
void who(std::vector<std::string> *vec, User & usr, Server & srv);
void whois(std::vector<std::string> *vec, User & usr, Server & srv);

// NICK.CPP
void nick(std::vector<std::string> *vec, User & usr, Server & srv);

// USER.CPP
void user(std::vector<std::string> *vec, User & usr, Server & srv);

// PRIVMSG.CPP
void	privmsg(std::vector<std::string> *vec, User & usr, Server & srv);
bool	privmsg_user(std::vector<std::string> *vec, User & usr, Server & srv);
bool	privmsg_channel(std::vector<std::string> *vec, User & usr, Server & srv, std::string msg);

// OPER.CPP
void oper(std::vector<std::string> *vec, User & usr, Server & srv);

// MODE.CPP
void mode(std::vector<std::string> *vec, User & usr, Server & srv);

// CAP.CPP
void cap(std::vector<std::string> *vec, User & usr, Server & srv);

// MODE_CHAN
void mode_chan(std::vector<std::string> *vec, User & usr, Server & srv);

//UTILS.CPP
void broadcast_update(User & usr, Server & srv, std::string command, std::string params);
bool check_nick(std::string str);
bool check_nick_availibility(std::string str, Server & srv);
bool check_user_name(std::string str);
std::map<int, std::string> get_msgs(void);
std::string  get_user_prefix(User usr);
std::string prefix(int num);
std::string allupper(std::string str);

//SEND.CPP
void send_msg(std::string msg, User &usr);
void send_msg2(int num, User & usr, std::string msg);
void send(std::string str, int fd);
void send_error(int err, User & usr);
void send_error(int err, User & usr, std::string ctx);
void send_rpl(int rpl, User & usr);
void send_rpl(int rpl, User & usr, std::string s1);
void send_rpl(int rpl, User & usr, std::string s1, std::string s2);
void send_update(User & usr, std::string cmd, std::string params, int fd);
void send_general_update(User & usr, Channel & chan, std::string cmd, std::string args, bool exclude_sender);
void send_privmsg(User & usr, Server & srv, std::string command, std::string params, int fd);
void send_whois(User & usr,User & tom, Server srv);
void send_who(User & usr, std::string chan_name,User & us);

//REGISTRATION.CPP
bool register_user(User & usr, Server & srv);

//PONG.CPP
void ping(std::vector<std::string> *vec, User & usr, Server & srv);
void pong(std::vector<std::string> *vec, User & usr, Server & srv);

//MODE_CHANS_CPP
void mode_chan(std::vector<std::string> *vec, User & usr, Server & srv);

//FIND_HOST_CPP
void find_host(User &);

//CONF.CPP
Server	configure(char *path);

// QUIT.CPP
void	quit(std::vector<std::string> *vec, User & usr, Server & srv);

// PART.CPP
void	part(std::vector<std::string> *vec, User & usr, Server & srv);

#endif
