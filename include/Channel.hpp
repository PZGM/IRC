#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"

class Channel
{
	private:

		std::string		_name;
		std::list<User> _user;
	public:

		Channel(){};
		Channel(string name, User & usr): _name(name)
		{
			_user.push_front(usr);
		};
		virtual	~Channel(){};


		std::string		get_name(){return _name;}
};


#endif