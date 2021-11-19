#include "../include/server.hpp"

void	who(std::vector<std::string> *vec, User & usr, Server & srv)
{
	bool op = false;
	if (vec->back() == "o") { //search just for operator
		op = true;
		vec->pop_back();
	}
	std::vector<std::string> uchan;
	std::vector<std::string>::iterator uit;
	Channel chan;
	std::list<User> lst;
	std::list<User>::iterator it;

	if (vec->size() == 0 || (vec->size() == 1  && vec->front() == "0"))
	{
		uchan = usr.get_channels();
		for (uit = uchan.begin(); uit != uchan.end(); uit++) {
			lst = srv.get_channel_by_name(*uit).get_users();
			for(it = lst.begin(); it != lst.end(); it++){
				if ((op == true && (*it).is_oper() == false) || ( vec->front() == "0" && (*it).get_inv()))
					continue;
				send((*it).get_nick(),(*it).get_fd());
			}
		}
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
