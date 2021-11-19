#include "../include/server.hpp"

void	who(std::vector<std::string> *vec, User & usr, Server & srv)
{
	bool op = false;
	if (vec->back() == "o") { //search just for operator
		op = true;
		vec->pop_back();
	}
	Channel chan;
	std::map<int, User> users = srv.get_users();;
	std::list<User> lst;
	std::list<User>::iterator it;
	if (vec->size() == 1  && vec->front() == "0")
	{
		for (std::map<int, User>::iterator it = users.begin(); it != users.end(); it++) {
				if (((op == true && it->second.is_oper() == false) || it->second.get_inv()) && it->first != usr.get_fd())
					continue;
				send_who(usr,"",  it->second, srv);
			}
			send_error(315, usr, vec->back(),srv);
		return;
	}
	else 
	{
		std::vector<std::string> chans = usr.get_channels();
		std::list<int> fds;
		fds.push_back(usr.get_fd());
		for(std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); it++) {
			Channel chan = srv.get_channel_by_name(*it);
			std::list<User> users = chan.get_users();
			for(std::list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
				fds.push_back(ite->get_fd());
			}
		}
		fds.sort();
		fds.unique();
		std::list<int>::iterator it = fds.begin();

		while (it != fds.end()) {
			if (srv.find_user_by_fd(*it)) {
				User & us = srv.get_user_by_fd(*it);
				if(us.get_inv() == false || us.get_inv())
				{
					if (vec->back()[0] != '#')
					{
						if (us.get_channels().empty() == false)
							send_who(usr, us.get_channels().back(), us, srv);
					}
					else
						send_who(usr, vec->back(), us, srv);
				}
			}
			it++;
		}
		send_error(315, usr, vec->back(),srv);

		return;
	}
}
