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
		bool			_isOper;
		bool			_invisible;
		vector<string>	_channel;
		vector<time_t>	_log; //0 = last registration; 1 = last change



	public:

		User() : _userName(""), _realName(""), _nickName(""), _pass(""), _fd(-1), _flags(false), _registred(false), _isOper(false), _invisible(false) {};
		User(int fd) : _userName(""), _realName(""), _nickName(""), _pass(""), _fd(fd), _flags(false), _registred(false), _isOper(false), _invisible(false) {};
		User(const User & src) {
			_userName = src._userName;
			_realName = src._realName;
			_nickName = src._nickName;
			_pass = src._pass;
			_fd = src._fd;
			_flags = src._flags;
			_registred = src._registred;
			_isOper = src._isOper;
			_invisible = src._invisible;
		}

		virtual	~User(){};

		void set_oper(bool oper) {
			_isOper = oper;
		}
		void set_inv(bool in) {
			_invisible = in;
		}

		bool is_oper(void) const {
			return _isOper;
		}

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
		void set_real_name(std::string realName) {
			_realName = realName;
		}

		std::string get_nick(void) const {
			return _nickName;
		}
		std::string get_real_name(void) const {
			return _realName;
		}
		int get_fd(void) const {
			return _fd;
		}

		bool is_registred(void) const {
			return _registred;
		}
		bool get_inv(void) const {
			return _invisible;
		}

		void set_registred(bool registration) {
			_registred = registration;
		}

		void add_channel(string str)
		{
			_channel.push_back(str);
		}

		bool find_channel(string str)
		{
			vector<string>::iterator it = _channel.begin();
			while (it != _channel.end())
			{
				if ((*it) == str)
					return true;
				it++;
			}
			return false;
		}

		bool operator==(User & usr)
		{
			return (_fd == usr._fd);
		}

		vector<string> get_channels() {
			return _channel;
		}

		void	del_chan(string del_chan)
		{
			for(vector<string>::iterator it = _channel.begin(); it != _channel.end(); it++)
			{
				if ((*it) == del_chan)
				{
					_channel.erase(it);
					return;
				}
			}
		}

		void	set_log(time_t now)
		{
			_log.push_back(now);
			_log.push_back(now);
		}

		time_t	get_last_activity()
		{
			return _log.back();
		}

		void	set_last_activity(time_t now)
		{
			_log.pop_back();
			_log.push_back(now);
		}

		time_t	get_last_connection()
		{
			return _log.front();
		}
};


#endif