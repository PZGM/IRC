#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"
using namespace std;

class Server
{
	private:
		list<User>	_user;
		map<string, Channel> _channel;
		string		_name;
		// bool		_mp;

	public:

		Server(){};
		virtual	~Server(){};

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
};


#endif