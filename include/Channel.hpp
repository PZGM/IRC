#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"

void send_update(User & usr, string command, string params);

class Channel
{
	private:

		string		_name;
		list<User>	_user;
		list<int>	_operators;
		string		_mode;
	
	public:

		Channel(){};
		Channel(string name, User & usr): _name(name)
		{
			_user.push_front(usr);
			_mode = "+nt";
		};
		virtual	~Channel(){};

		list<User> get_users() const {
			return _user;
		}

		string		get_name() const {
			return _name;
		}

		string		get_mode() const {
			return _mode;
		}
		
		bool find_user(User & usr)
		{
			list<User>::iterator it = _user.begin();
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
			cout << "Bonsoir PARIIIIIIIIS" << endl;
			cout << "list user = " << _user.size() << endl;
			for (list<User>::iterator it = _user.begin(); it != _user.end(); it++)
			{
				cout << "it fd = |" << (*it).get_fd() <<"|" << endl;
				cout << "it fd = |" << forbiden_usr->get_fd() <<"|" << endl;
				if (forbiden_usr == NULL || (*it).get_fd() != forbiden_usr->get_fd())
				{
					send_update((*it),cmd, msg);
				}
			}
		}
};


#endif