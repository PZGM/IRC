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
		privmsg_user(vec, usr, srv);
	}
	else if (srv.find_channel(vec->front()) != false)
	{
		std::cout << "================j ai un channel" << std::endl;
		privmsg_channel(vec, usr, srv);
	}
	else
	{
		if (vec->front()[0] != '#')
			send_error(401, usr);
		else
			send_error(403, usr, vec->front());
	// :ergo.test 401 fd g :No such nick
	// :ergo.test 403 fd g :No such channel
		return ;
	}
}

bool	privmsg_user(vector<string> *vec, User & usr, Server & srv)
{
	if (srv.find_user(vec->front()) != false)
	{
		int i = srv.get_fd_from_nick(vec->front());
		vec->erase(vec->begin());
		send_privmsg(usr, srv, "PRIVMSG", vec->front(), i);
	}
	else
	{
		send_error(401, usr);
	// :ergo.test 401 fd g :No such nick
		return false;
	}
	return true;
}

bool	privmsg_channel(vector<string> *vec, User & usr, Server & srv)
{
	map<string, Channel>::iterator it = srv.get_begin_channel();
	while(it != srv.get_end_channel())
	{
		if ((*it).first == vec->front() && (*it).second.find_user(usr) == true)
		{
			std::string cmd = "PRIVMSG " + vec->front();
			vec->erase(vec->begin());
			(*it).second.general_msg(cmd, vec->front(), &usr);
			return true;
		}
		it++;
	}
	return false;
}

#endif
