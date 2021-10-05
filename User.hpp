#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
class User
{
	private:
		std::string 	_real_name;
		std::string		_nick_name;
		std::string 	_pass;
		int				_fd;
		bool			_flags;




	public:

		User() : _real_name(""), _nick_name(""), _pass(""), _fd(-1), _flags(false){};
		User(int fd) : _real_name(""), _nick_name(""), _pass(""), _fd(fd), _flags(false) {};
		User(const User & src) {
			_real_name = src._real_name;
			_nick_name = src._nick_name;
			_pass = src._pass;
			_fd = src._fd;
			_flags = src._flags;
		}
		virtual	~User(){};

		bool set_nick(std::string nick) {
			_nick_name = nick;
			return true;
		}

		void print() {
			if (_flags == true)
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") is op"<< std::endl;
			else
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") isnt op" << std::endl; 
		}

};


#endif