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
	// if (srv.find_channel(vec->front()) == false)
	// {
	// 	std::cout << "no channel" << std::endl;
	// 	send_error(403, usr); //:ergo.test 403 fg yolo :No such channel
	// 	return;
	// }
	map<string, Channel>::iterator it = srv.get_begin_channel();
	while(it != srv.get_end_channel())
	{
		if ((vec->front()).compare((*it).first) == 0)
		{
			if (usr.find_channel(vec->front()) == false || srv.find_chan_user(usr, (*it).second) == false)
			{
				usr.add_channel(vec->front());
				srv.add_user_channel(usr, vec->front());
				(*it).second.general_join_msg(vec->front(), &usr);
				(*it).second.join_msg(usr);
			}
			return;
		}
		it++;
	}
	if (it == srv.get_end_channel())
	{
		Channel chan(vec->front(), usr);
		usr.add_channel(vec->front());
		srv.add_channel(chan);
		chan.join_msg(usr);
	}
}




#endif



/*
- dans join lorsque le user join le channel la lsite le nom du chan s'affiche et des gens dedans s'affiche et les operator avec un @

*/