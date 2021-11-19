#ifndef OPER_CPP
# define OPER_CPP

#include "../include/server.hpp"

void	oper(std::vector<std::string> *vec, User & usr, Server & srv)
{
	if (usr.is_oper()) {
		send_error(400, usr, "OPER",srv);
		return;
	}
	std::string name = vec->front();
	std::string pass = (vec->size() == 1) ? "" : (*vec)[1];
	if (srv.check_oper(name, pass) == false) {
		send_error(464, usr, "OPER",srv);
		return;
	}
	usr.set_oper(true);
	send_rpl(381, usr, srv);
	std::string str = "MODE ";
	str += usr.get_nick();
	str += " +o";
	send_msg(str, usr,srv);
}

#endif