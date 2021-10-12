#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
using namespace std;

class User
{
	private:
		std::string 	_userName;
		std::string 	_realName;
		std::string		_nickName;
		std::string 	_pass;
		int				_fd;
		bool			_flags;
		bool			_registred;




	public:

		User() : _userName(""), _realName(""), _nickName(""), _pass(""), _fd(-1), _flags(false), _registred(false){};
		User(int fd) : _userName(""), _realName(""), _nickName(""), _pass(""), _fd(fd), _flags(false), _registred(false) {};
		User(const User & src) {
			_userName = src._userName;
			_realName = src._realName;
			_nickName = src._nickName;
			_pass = src._pass;
			_fd = src._fd;
			_flags = src._flags;
			_registred = src._registred;
		}
		virtual	~User(){};

		void set_nick(std::string nick) {
			_nickName = nick;
		}
		bool set_real(std::string real) {
			_realName = real;
			return true;
		}
		bool set_user(std::string user) {
			_userName = user;
			return true;
		}
		bool set_flags(std::string flag) {
			if (flag[0] == '1')
				_flags = true;
			else
				_flags = false;
			return true;
		}

		std::string getNick(void) const {
			return _nickName;
		}

		std::string getRealName(void) const {
			return _realName;
		}

		void setRealName(std::string realName) {
			_realName = realName;
		}

		int get_fd(void) const {
			return _fd;
		}

		bool isRegistred(void) const {
			return _registred;
		}

		void setRegistred(bool registration) {
			_registred = registration;
		}



		void print() {
			if (_flags == true)
				std::cout << "USER _ " << _fd << " : " << _nickName << "(" << _realName << ") is op"<< std::endl;
			else
				std::cout << "USER _ " << _fd << " : " << _nickName << "(" << _realName << ") isnt op" << std::endl; 
		}

};


#endif