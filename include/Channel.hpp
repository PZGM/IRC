#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"

void send_update(User & usr, std::string command, std::string params);

class Channel
{
	private:

		std::string		_name;
		std::list<User> _user;
		std::list<int> _operators;
	public:

		Channel(){};
		Channel(string name, User & usr): _name(name)
		{
			_user.push_front(usr);
		};
		virtual	~Channel(){};

		list<User> get_users() const {
			return _user;
		}

		std::string		get_name(){
			return _name;
		}
		
		bool find_user(User & usr)
		{
			std::list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				if ((*it) == usr)
					return true;
				it++;
			}
			return false;
		}

		void	add_user(User &usr)
		{
			_user.push_front(usr);
		}

		void	add_oper(User & usr){
			_operators.push_back(usr.get_fd());
		}

		void	rm_oper(User & usr) {
			_operators.remove(usr.get_fd());
		}

		bool	is_oper(User & usr) {
			list<int>::iterator it = _operators.begin();
			while (it != _operators.end()) {
				if (*it == usr.get_fd())
					return true;
				it++;
			}
			return false;
		}

		void	general_msg(string cmd, string msg, User * forbiden_usr = NULL)
		{
			std::cout << "Bonsoir PARIIIIIIIIS" << std::endl;
			std::cout << "list user = " << _user.size() << std::endl;
			for (std::list<User>::iterator it = _user.begin(); it != _user.end(); it++)
			{
				std::cout << "it fd = |" << (*it).get_fd() <<"|" << std::endl;
				std::cout << "it fd = |" << forbiden_usr->get_fd() <<"|" << std::endl;
				if (forbiden_usr == NULL || (*it).get_fd() != forbiden_usr->get_fd())
				{
					send_update((*it),cmd, msg);
				}
			}
		}
};


#endif