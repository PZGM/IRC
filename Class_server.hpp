#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"

class Server
{
	private:
		list<User>	_user;
		map<string, Channel> _channel;
		string		_name;
		bool		_mp;
	public:

		Server();
		Server();
		virtual	~Server();

};


#endif