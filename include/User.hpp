#ifndef USER_HPP
# define USER_HPP

# include "server.hpp"
using namespace std;

class User
{
	private:
		std::string 			_user_name;
		std::string 			_real_name;
		std::string				_nick_name;
		std::string 			_pass;
		int						_fd;
		bool					_flags;
		bool					_registred;
		std::vector<string>		_op_channel;





	public:

		User() : _real_name(""), _nick_name(""), _pass(""), _fd(-1), _flags(false), _registred(false){};
		User(int fd) : _real_name(""), _nick_name(""), _pass(""), _fd(fd), _flags(false), _registred(false) {};
		User(const User & src) {
			_real_name = src._real_name;
			_nick_name = src._nick_name;
			_pass = src._pass;
			_fd = src._fd;
			_flags = src._flags;
			_registred = src._registred;
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
		void set_real_name(std::string realName) {
			_real_name = realName;
		}

		std::string get_nick(void) const {
			return _nick_name;
		}
		std::string get_real_name(void) const {
			return _real_name;
		}
		int get_fd(void) const {
			return _fd;
		}

		bool is_registred(void) const {
			return _registred;
		}

		void set_registred(bool registration) {
			_registred = registration;
		}

		void add_channel(string str)
		{
			_op_channel.insert((_op_channel.end())--, str);
		}

		bool find_channel(string str)
		{
			vector<string>::iterator it = _op_channel.begin();
			while (it != _op_channel.end())
			{
				if ((*it) == str)
					return true;
				it++;
			}
			return false;
		}

		void print() {
			if (_flags == true)
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") is op"<< std::endl;
			else
				std::cout << "USER _ " << _fd << " : " << _nick_name << "(" << _real_name << ") isnt op" << std::endl; 
		}

};


#endif