#ifndef PRIVMSG_CPP
# define PRIVMSG_CPP

#include "../include/server.hpp"

	// :ergo.test 451 * :You need to register before you can use that command

void	privmsg(vector<string> *vec, User & usr, Server & srv)
{
	if (vec->size() < 2)
	{
		send_error(461, usr);
		return;
	// :ergo.test 461 fg PRIVMSG :Not enough parameters
	}
	if (srv.find_user(vec->front()) != false)
	{
		int i = srv.get_fd_from_nick(vec->front());
		vec->erase(vec->begin());
		send(vec->front(),i);
	}
	else
	{
		send_error(401, usr);
	// :ergo.test 401 fd g :No such nick
		return ;
	}
}

#endif