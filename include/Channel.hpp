#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"

class Server;

void send(std::string str, int fd);
void send_msg2(int num, User & usr, std::string msg, Server & srv);
void send_error(int err, User & usr, std::string ctx, Server & srv);


class Channel
{
	private:

		std::string		_name;
		std::list<User>	_user;
		std::list<int>	_operators;
		std::string		_mode;
	
	public:

		Channel(){
			_mode = "+nt";

		};
		
		Channel(std::string name, User & usr): _name(name)
		{
			_user.push_front(usr);
			_operators.push_back(usr.get_fd());
			_mode = "+nt";
		};
		virtual	~Channel(){};

		std::list<User> get_users() const {
			return _user;
		}

		std::string		get_name() const {
			return _name;
		}

		std::list<int>	get_oper() const{
			return _operators;
		}

		std::string		get_mode() const {
			return _mode;
		}
		
		bool find_user(User & usr)
		{
			std::list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				if (*it == usr)
					return true;
				it++;
			}
			return false;
		}

		bool find_user(std::string nick)
		{
			std::list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				if ((it->get_nick()) == nick)
					return true;
				it++;
			}
			return false;
		}

		void	add_user(User &usr )
		{
			_user.push_back(usr);
		}

		void	add_oper(User & usr){
			_operators.push_back(usr.get_fd());
		}

		void	rm_oper(User & usr) {
			_operators.remove(usr.get_fd());
		}

		void	add_oper(int fd){
			_operators.push_back(fd);
		}

		void	rm_oper(int fd) {
			_operators.remove(fd);
		}

		bool	is_oper(User & usr) {
			std::list<int>::iterator it = _operators.begin();
			while (it != _operators.end()) {
				if (*it == usr.get_fd())
					return true;
				it++;
			}
			return false;
		}

		void	del_user(User & usr)
		{
			for (std::list<int>::iterator it = _operators.begin(); it != _operators.end(); it++)
			{
				if (usr.get_fd() == (*it))
				{
					_operators.erase(it);
					break;
				}
			}
			for (std::list<User>::iterator it = _user.begin(); it != _user.end(); it++)
			{
				if (usr.get_nick() == (*it).get_nick())
				{
					std::cout << "==========================" << (*it).get_nick() << std::endl;
					_user.erase(it);
					break;
				}
			}
		}
};


#endif
