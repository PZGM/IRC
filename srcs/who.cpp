#include "../include/server.hpp"

void	who(vector<string> *vec, User & usr, Server & srv)
{
	bool op = false;
	if (vec->back() == "o") { //search just for operator
		op = true;
		vec->pop_back();
	}
	vector<string> uchan;
	vector<string>::iterator uit;
	Channel chan;
	list<User> lst;
	list<User>::iterator it;

	if (vec->size() == 0 || (vec->size() == 1  && vec->front() == "0"))
	{
		uchan = usr.get_channels();
		for (uit = uchan.begin(); uit != uchan.end(); uit++) {
			lst = srv.get_channel_by_name(*uit).get_users();
			for(it = lst.begin(); it != lst.end(); it++){
				if (op == true && (*it).is_oper() == false)
					continue;
				send((*it).get_nick(),(*it).get_fd());//send le machin
			}
		}
		return;
	}
	else 
	{
		vector<string> chans = usr.get_channels();
		list<int> fds;
		fds.push_back(usr.get_fd());
		for(vector<string>::iterator it = chans.begin(); it != chans.end(); it++) {
			Channel chan = srv.get_channel_by_name(*it);
			list<User> users = chan.get_users();
			for(list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
				fds.push_back(ite->get_fd());
			}
		}
		fds.sort();
		fds.unique();
		list<int>::iterator it = fds.begin();

		while (it != fds.end()) {
			if (srv.find_user_by_fd(*it)) {
				User & us = srv.get_user_by_fd(*it);
				if(us.get_inv() == false)
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
		send_error(315, usr, vec->back());

		return;
	}
}
