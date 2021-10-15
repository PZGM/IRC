#ifndef MODE_CPP
# define MODE_CPP

#include "../include/server.hpp"

void	mode(vector<string> *vec, User & usr, Server & srv)
{
	if (vec->front() != usr.get_nick())
		send_error(502, usr);
	if (vec->size() > 1) {
		if ((*vec)[1] == "-o")
			usr.set_oper(false);
		else if ((*vec)[1] == "+o")
			;
		else {
			send_error(501, usr, (*vec)[1]);
			return;
		}
	}
}

#endif