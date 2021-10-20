#ifndef CONF_CPP
# define CONF_CPP

#include "../include/server.hpp"

Server	configure()
{
	std::ifstream file("conf.conf");
	string port;
	getline(file, port);
	port.erase(0, 5);
	string mdp;
	getline(file, mdp);
	mdp.erase(0, 5);
	Server srv(port, mdp);
	return srv;
}

#endif