#ifndef OPER_CPP
# define OPER_CPP

#include "../include/server.hpp"

void	oper(vector<string> *vec, User & usr, Server & srv)
{
	if (usr.is_oper()) {
		send_error(400, usr, "OPER");
		return;
	}
	string name = vec->front();
	string pass = (vec->size() == 1) ? "" : (*vec)[1]();
	if (check_oper(name, pass) == false) {
		send_error(464, usr, "OPER");
		return;
	}
	usr.set_oper(true);
	send_rpl(381, usr);
	string str = "MODE ";
	str += usr.get_nick();
	str += " +o";
	send_msg(str, usr);
}

#endif