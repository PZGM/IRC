#ifndef JOIN_CPP
# define JOIN_CPP

#include "../include/server.hpp"

void	join(vector<string> *vec, User & usr, Server & srv)
{
	if (usr.is_registred() == false)
		send_error(451, usr); //:ergo.test 451 * :You need to register before you can use that command
	if (vec->front()[0] != '#')
		send_error(461, usr); //:ergo.test 461 fg JOIN :Not enough parameters
	if (srv.find_channel(vec->front()) == false)
		send_error(403, usr); //:ergo.test 403 fg yolo :No such channel
	map<string, Channel>::iterator it = srv.get_begin_channel();
	while(it != srv.get_end_channel())
	{
		if ((vec->front()).compare((*it).first) == 0)
		{
			// std::cout << "Il faut join" << std::endl;
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




#endif