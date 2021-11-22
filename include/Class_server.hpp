#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"
#define FD_MAX 2000
#define SERVER_ADDR "138.68.159.15"

class Server
{
	private:
		std::map<int, User> _users; //fd, User
		std::map<std::string, Channel> _channel; //name, Channel
		std::map<std::string, std::string> _operators;
		std::string		_name;
		time_t 		_tm;
		std::string		_passw;
		std::string		_host;
		int			_port;
		std::string		_motd;
		// bool		_mp;

	public:
		struct pollfd fds[FD_MAX];

		Server( std::string p, std::string name):_name("irc." + name){
			for (std::string::iterator it = p.begin(); it != p.end(); it++) {
				if (std::isdigit(*it) == 0) {
				exit(0);
				}
			}
			_port = std::stoi(p); //definir des values limites
			_users = std::map<int, User>();
			_tm = time(NULL);
			_operators = std::map<std::string, std::string>();
			_operators["admin"] = "admin";
		};
		
		Server(){
			_users = std::map<int, User>();
		};

		virtual	~Server(){};

		void	set_name(std::string name){_name = name;}
		void	set_motd(std::string motd){_motd = motd;}
		void	set_op(std::map<std::string, std::string> op){_operators = op;}
		std::map<int, User> & get_users(void)
		{
			return _users;
		}

		std::map<std::string, Channel>::iterator get_begin_channel()
		{
			return(_channel.begin());
		}

		std::map<std::string, Channel>::iterator get_end_channel()
		{
			return(_channel.end());
		}

		bool	find_channel(std::string str)
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

		bool	find_user(std::string nick)
		{
			for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick && (*it).second.is_registred())
					return true;
			}
			return false;
		}

		User	&get_user(std::string nick)
		{
			for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick && (*it).second.is_registred())
					return it->second;
			}
			return (_users.begin()->second);
		}

		std::string	get_creation_time(void) const {
			std::string str = "";
			struct tm * curtime = localtime ( &_tm );
			str += asctime(curtime);
			if (*(str.end() - 1) == '\n')
				str.resize(str.size() - 1);
			return str;
		}

		int		get_fd_from_nick(std::string nick)
		{
			for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_nick() == nick)
					return (*it).first;
			}
			return 0;
		}

		std::string		get_nick_from_fd(int fd)
		{
			for (std::map<int, User>::iterator it = _users.begin(); it != _users.end(); it++)
			{
				if ((*it).second.get_fd() == fd)
					return (*it).second.get_nick();
			}
			return 0;
		}

		int get_port() {
			return _port;
		}

		std::string get_host() const {
			return _host;
		}

		std::string get_motd() const {
			return _motd;
		}

		void set_host(std::string host) {
			_host = host;
		}

		bool check_oper(std::string name, std::string pass) {
			if (_operators.count(name) == 0) {
				return false;
			}	
			if (_operators[name] != pass){
				return false;
			}
			return true;
		}
		void	add_user_channel(User &usr, std::string chan_name)
		{
			_channel[chan_name].add_user(usr);
		}

		Channel & get_channel_by_name(std::string name) {			
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
		
		void kick_user(int fd) {
			User lya;
			std::vector<std::string>::iterator lily;
			if (find_user_by_fd(fd)) {
				lya = get_user_by_fd(fd);
				lily = lya.get_channels().begin();
				for(; lily != lya.get_channels().end(); lily++) {
					get_channel_by_name(*lily).del_user(lya);
				}
			del_user(lya);
			}
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

		std::string get_name()
		{
			return _name;
		}

		void del_chan(std::string chan)
		{
			_channel.erase(chan);
			std::map<int, User>::iterator it = _users.begin();
			while (it != _users.end()) {
				it->second.del_chan(chan);
				it++;
			}
		}
};


#endif
