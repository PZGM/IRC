#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include "server.hpp"

void send_update(User & usr, string command, string params);
void send(std::string str, int fd);

class Channel
{
	private:

		string		_name;
		list<User>	_user;
		list<int>	_operators;
		string		_mode;
	
	public:

		Channel(){
			_mode = "+nt";

		};
		Channel(string name, User & usr): _name(name)
		{
			_user.push_front(usr);
			_operators.push_back(usr.get_fd());
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
				if (*it == usr)
					return true;
				it++;
			}
			return false;
		}

		bool find_user(string nick)
		{
			std::cout << "nick === " << nick << " size = " << _user.size() << std::endl;
			list<User>::iterator it = _user.begin();
			while (it != _user.end())
			{
				std::cout << "===> " << it->get_nick() << std::endl;
				if ((it->get_nick()) == nick)
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

		void	add_oper(int fd){
			_operators.push_back(fd);
		}

		void	rm_oper(int fd) {
			_operators.remove(fd);
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

		void	
		    general_msg(string cmd, string msg, User * forbiden_usr = NULL)
		{
			for (list<User>::iterator it = _user.begin(); it != _user.end(); it++)
			{
				if (forbiden_usr == NULL || (*it).get_fd() != forbiden_usr->get_fd())
				{
					send_update((*it),cmd, msg);
				}
			}
		}

		void	join_msg(User & usr)
		{
			string msg = _name;

			msg += " :";
			
			for (list<User>::iterator uit = _user.begin(); uit != _user.end(); uit++)
			{
				for(list<int>::iterator fdit = _operators.begin(); fdit != _operators.end(); fdit++)
					if ((*fdit) == (*uit).get_fd())
						msg += "@";
				msg += (*uit).get_nick();
				if (++uit != _user.end())
					msg += " ";
				uit--;
			}
			msg += "\n";
			send(msg, usr.get_fd());
		}

};


#endif