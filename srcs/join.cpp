#ifndef JOIN_CPP
# define JOIN_CPP

#include "../include/server.hpp"

void	join(vector<string> *vec, User & usr, Server & srv)
{
	if (vec->size() == 0)
	{
		std::cout << "no parameter" << std::endl;
		send_error(461, usr); //:ergo.test 461 fg JOIN :Not enough parameters
		return;
	}
	if (vec->front()[0] != '#' || srv.find_channel(vec->front()) == false)
	{
		std::cout << "no channel" << std::endl;
		send_error(403, usr); //:ergo.test 403 fg yolo :No such channel
		return;
	}
	vec->front().erase(0, 1);
	map<string, Channel>::iterator it = srv.get_begin_channel();
	while(it != srv.get_end_channel())
	{
		if ((vec->front()).compare((*it).first) == 0)
		{
			if (usr.find_channel(vec->front()) == false || srv.find_chan_user(usr, (*it).second) == false)
				usr.add_channel(vec->front());
			return;
		}
		it++;
	}
	if (it == srv.get_end_channel())
	{
		Channel chan(vec->front(), usr);
		usr.add_channel(vec->front());
		srv.add_channel(chan);
	}
}


// check si le user et deja dans le channel si oui il dit rien


#endif