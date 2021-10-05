#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
class User
{
	private:
		std::string 	_real_name;
		std::string		_nick_name;
		std::string 	_mdp;
		struct pollfd	_fds[FD_MAX];
		bool			_droit;




	public:

		User(){};
		virtual	~User(){};

};


#endif