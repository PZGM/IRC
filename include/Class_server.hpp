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
		// bool		_mp;

	public:

		Server(){
			_users = map<int, User>();
		};
		
		virtual	~Server(){};

		map<int, User> & get_users(void) {
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

		bool find_chan_user(User & usr, Channel chan)
		{
			return chan.find_user(usr);
		}
};


#endif