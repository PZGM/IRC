#ifndef MODE_CPP
# define MODE_CPP

#include "../include/server.hpp"

void	mode(vector<string> *vec, User & usr, Server & srv)
{
	(void)srv;
	if (vec->front() != usr.get_nick()) {
		send_error(502, usr);
		return;
	}
	if (vec->size() > 1) {
		if ((*vec)[1] == "-o") {
			send_update(usr, srv, "MODE", (*vec)[0] + " " + (*vec)[1]);
			usr.set_oper(false);
		}
		else if ((*vec)[1] == "+o")
			;
		else {
			send_error(501, usr, (*vec)[1]);
			return;
		}
	}
}

#endif