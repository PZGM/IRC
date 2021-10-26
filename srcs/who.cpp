
#include "../include/server.hpp"

void	who(vector<string> *vec, User & usr, Server & srv)
{
	bool op = false;
	// if (vec->size() > 2 || (vec->size() == 2 && vec->back() != "o"))
	// {
	// 	std::cerr << "error args who" << std::endl;
	// 	send_error(461,usr); //random value in send error need to find the good one
	// 	return;
	// }
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
		std::cout << "===========================je suis dans le if" << std::endl;
		uchan = usr.get_channels();
		for (uit = uchan.begin(); uit != uchan.end(); uit++) {
			lst = srv.get_channel_by_name(*uit).get_users();
			// lst = chan.get_users();
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
		std::cout << "===========================je suis dans le else" << std::endl;
		// uchan = usr.get_channels();
		// for (uit = uchan.begin(); uit != uchan.end(); uit++) {
		// 	std::cout << "uit = " << (*uit)<< std::endl;
		// 	lst = srv.get_channel_by_name((*uit)).get_users();
		// 	// lst = chan.get_users();
		// 	for(it = lst.begin(); it != lst.end(); it++){
		// 		if (op == true && (*it).is_oper() == false)
		// 			continue;
		// 			std::cout << "get nick = " << (*it).get_nick()<< std::endl;
		// 			std::cout << "back = " << vec->back() << std::endl;
		// 			std::cout << "channel bool = " << (*it).find_channel(vec->back()) << std::endl;
		// 		if (((*it).get_nick() == vec->back()) || ((*it).find_channel(vec->back()))) {
		// 			std::cout << "j'affiche le msg" << std::endl;
		// 		send((*it).get_nick(),(*it).get_fd());//send le machin
		// 		}
		// 	}
		// }

		vector<string> chans = usr.get_channels();
		list<User> fds;
		fds.push_back(usr);
		for(vector<string>::iterator it = chans.begin(); it != chans.end(); it++) {
			Channel chan = srv.get_channel_by_name(*it);
			list<User> users = chan.get_users();
			for(list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
				fds.push_back(ite->get_fd());
			}
		}
		// fds.sort();
		// fds.unique();
		list<User>::iterator it = fds.begin();
		while (it != fds.end()) {
			std::cout << "coucou" << std::endl;
			// send_update(usr, srv, command, params, *it);
			std::cout << "nick =" << (*it).get_nick()<< std::endl;
			std::cout << "fd =" << (*it).get_fd()<< std::endl;
			send((*it).get_nick(),(*it).get_fd());//send le machin
			it++;
		}

		return;
	}
}