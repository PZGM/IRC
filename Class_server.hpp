#ifndef CLASS_SERVER_HPP
# define CLASS_SERVER_HPP

# include "server.hpp"

class Class_server
{
	private:
		list<User>	_user;
		string		_name;
		bool		_mp;
	public:

		Class_server();
		Class_server();
		virtual	~Class_server();

};


#endif