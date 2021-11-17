#ifndef QUIT_CPP
# define QUIT_CPP

#include "../include/server.hpp"

void	quit(std::vector<std::string> *vec, User & usr, Server & srv)
{
	std::string msg;
	for (std::vector<std::string>::iterator it = vec->begin();it != vec->end(); it++)
	{
		if (it != vec->begin())
			msg += " ";
		msg += (*it);
	}
	broadcast_update(usr, srv, "QUIT", msg);
	std::vector<std::string> del_chan = usr.get_channels();
	for (std::vector<std::string>::iterator it = del_chan.begin(); it != del_chan.end(); it++)
	{
		if (srv.find_channel((*it)) == true)
			srv.get_channel_by_name((*it)).del_user(usr);
	}
	int i = 0;
	while (usr.get_fd() != srv.fds[i].fd)
		i++;
	srv.del_user(usr);
	close(srv.fds[i].fd);
	srv.fds[i].fd = -1;
}
#endif