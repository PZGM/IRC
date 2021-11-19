#ifndef PART_CPP
# define PART_CPP

#include "../include/server.hpp"

void	part(std::vector<std::string> *vec, User & usr, Server & srv)
{
	std::vector<std::string> * del_chan = split(vec->front(), ",");
	for (std::vector<std::string>::iterator it = del_chan->begin(); it != del_chan->end(); it++)
	{
		if (srv.find_channel((*it)) == true)
		{
			std::string param = srv.get_channel_by_name((*it)).get_name();
			broadcast_update(usr, srv, "PART", param);
			srv.get_channel_by_name((*it)).del_user(usr);
			usr.del_chan(srv.get_channel_by_name((*it)).get_name());
			if (srv.get_channel_by_name((*it)).get_users().empty() == 0)
				srv.del_chan((*it));
		}
	}
}



#endif