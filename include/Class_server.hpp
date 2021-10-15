#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"
using namespace std;

class Server
{
	private:
		map<int, User> _users;
		map<string, Channel> _channel;
		string		_name;
		time_t 		_tm;
		string		_passw;
		int		_port;
		// bool		_mp;

	public:

		Server( string p, std::string passw): _passw(passw) {
		for (char const &c : p) {
        	if (std::isdigit(c) == 0)
			std::cout << "Port must be a number" << std::endl;
			exit(0);
    		}
		_port = std::stoi(p); //definir des values limites
			_users = map<int, User>();
			_tm = time(NULL);
		};
		
		Server(){
			_users = map<int, User>();
		};

		virtual	~Server(){};

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
				if ((*it).second.get_nick() == nick)
					return true;
			}
			return false;
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

		int get_port() {
			return _port;
		}
};


#endif
