#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
using namespace std;

class User
{
	private:
		std::string 	_user_name;
		std::string 	_real_name;
		std::string		_nick_name;
		std::string 	_pass;
		int				_fd;
		bool			_flags;
		bool			_exist;




	public:

		User() : _real_name(""), _nick_name(""), _pass(""), _fd(-1), _flags(false), _exist(false){};
		User(int fd) : _real_name(""), _nick_name(""), _pass(""), _fd(fd), _flags(false), _exist(false) {};
		User(const User & src) {
			_real_name = src._real_name;
			_nick_name = src._nick_name;
			_pass = src._pass;
			_fd = src._fd;
			_flags = src._flags;
			_exist = src._exist;
		}
		virtual	~User(){};

		void set_nick(std::string nick) {
			_nick_name = nick;
		}
		bool set_real(std::string real) {
			_real_name = real;
			return true;
		}
		bool set_user(std::string user) {
			_user_name = user;
			return true;
		}
		bool set_flags(std::string flag) {
			if (flag[0] == '1')
				_flags = true;
			else
				_flags = false;
			return true;
		}

		std::string get_nick(void) const {
			return _nick_name;
		}

		int get_fd(void) const {
			return _fd;
		}

		bool exist(void) const {
			return _exist;
		}

		void setExist(bool exist) {
			_exist = exist;
		}

		void print() {
			if (_flags == true)
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") is op"<< std::endl;
			else
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") isnt op" << std::endl; 
		}

};


#endif