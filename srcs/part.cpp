#ifndef PART_CPP
# define PART_CPP

#include "../include/server.hpp"

void	part(vector<string> *vec, User & usr, Server & srv)
{
	vector<string> * del_chan = split(vec->front(), ",");
	for (vector<string>::iterator it = del_chan->begin(); it != del_chan->end(); it++)
	{
		if (srv.find_channel((*it)) == true)
		{
			broadcast_update(usr, srv, "PART", srv.get_channel_by_name((*it)).get_name());
			srv.get_channel_by_name((*it)).del_user(usr);
			usr.del_chan(srv.get_channel_by_name((*it)).get_name());
		}
	}
}



#endif