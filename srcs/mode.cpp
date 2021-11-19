#ifndef MODE_CPP
# define MODE_CPP

#include "../include/server.hpp"

void	mode(std::vector<std::string> *vec, User & usr, Server & srv)
{
	if (vec->front()[0] == '#') {
		mode_chan(vec, usr, srv);
		return;
	}
	if (vec->front() != usr.get_nick()) {
		send_error(502, usr,srv);
		return;
	}
	if (vec->size() > 1) {
		if ((*vec)[1] == "-o") {
			send_update(usr, "MODE", (*vec)[0] + " " + (*vec)[1], usr.get_fd());
			usr.set_oper(false);
		}
		else if ((*vec)[1] == "+o") {
			if (usr.is_oper() == false)
				send_error(481, usr, srv);
		}
		else if ((*vec)[1] == "+i")
		{
			broadcast_update(usr, srv, "MODE " + (*vec)[0], (*vec)[1]);
			usr.set_inv(true);
		}
		else if ((*vec)[1] == "-i")
		{
			usr.set_inv(false);
		}
		else {
			send_error(501, usr, (*vec)[1],srv);
			return;
		}
	}
}

#endif
