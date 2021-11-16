#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"
using namespace std;
#define FD_MAX 2000

class Server
{
	private:
		map<int, User> _users; //fd, User
		map<string, Channel> _channel; //name, Channel
		map<string, string> _operators;
		string		_name;
		time_t 		_tm;
		string		_passw;
		string		_host;
		int			_port;
		string		_motd;
		// bool		_mp;

	public:
		struct pollfd fds[FD_MAX];

		Server( string p, std::string passw): _passw(passw) {
		for (string::iterator it = p.begin(); it != p.end(); it++) {
        	if (std::isdigit(*it) == 0) {
			exit(0);
    		}
		}
		_port = std::stoi(p); //definir des values limites
			_users = map<int, User>();
			_tm = time(NULL);
			_operators = map<string, string>();
			_operators["admin"] = "admin";
		};
		
		Server(){
			_users = map<int, User>();
		};

		virtual	~Server(){};

		void	set_name(string name){_name = name;}
		void	set_motd(string motd){_motd = motd;}
		void	set_op(map<string,string> op){_operators = op;}
		map<int, User> & get_users(void)
		{
			return _users;
		}

		map<string, Channel>::iterator get_begin_channel()
		{
			return(_channel.begin());
		}

		map<string, Channel>::iterator get_end_channel()
		{
			return(_channel.end());
		}

		bool	find_channel(string str)
		{
			if (_channel.find(str) != _channel.end())
				return true;
			return false;
		}
		void	add_channel(Channel chan)
		{
			_channel[(chan.get_name())] = chan;
		}

		bool	find_chan_user(User & usr, Channel chan)
		{
			return chan.find_user(usr);
		}

		bool	find_user(string nick)
		{
			for (map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick && (*it).second.is_registred())
					return true;
			}
			return false;
		}

		User	&get_user(string nick)
		{
			for (map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick && (*it).second.is_registred())
					return it->second;
			}
			return (_users.begin()->second);
		}

		string	get_creation_time(void) const {
			string str = "";
			struct tm * curtime = localtime ( &_tm );
			str += asctime(curtime);
			if (*(str.end() - 1) == '\n')
				str.resize(str.size() - 1);
			return str;
		}

		int		get_fd_from_nick(string nick)
		{
			for (map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick)
					return (*it).first;
			}
			return 0;
		}

		string		get_nick_from_fd(int fd)
		{
			for (map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_fd() == fd)
					return (*it).second.get_nick();
			}
			return 0;
		}

		int get_port() {
			return _port;
		}

		string get_host() const {
			return _host;
		}

		string get_motd() const {
			return _motd;
		}

		void set_host(string host) {
			_host = host;
		}

		bool check_oper(string name, string pass) {
			if (_operators.count(name) == 0) {
				return false;
			}	
			if (_operators[name] != pass){
				return false;
			}
			return true;
		}
		void	add_user_channel(User &usr, string chan_name)
		{
			_channel[chan_name].add_user(usr);
		}

		Channel & get_channel_by_name(string name) {
			return _channel[name];
		}

		User & get_user_by_fd(int fd) {
			return _users[fd];
		}

		bool find_user_by_fd(int fd) {
			if (_users.count(fd) != 0)
				return true;
			return false;
		}

		void	del_user(User & usr)
		{
			_users.erase(usr.get_fd());
		}

		void	set_fds(int sockfd)
		{
			memset(fds,0, sizeof(fds));
			fds[0].fd = sockfd;
			fds[0].events = POLLIN;
		}

		pollfd* get_fds()
		{
			return fds;
		}

};


#endif
