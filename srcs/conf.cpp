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
	
	string motd;
	getline(file, motd);
	motd.erase(0, 5);
	srv.set_motd(motd);
	
	string name;
	getline(file, name);
	name.erase(0, 5);
	srv.set_name(name);

	string oper;
	getline(file, oper);
	oper.erase(0, 5);
	vector<string> *op = split(oper, "|");
	map<string, string> operatr;
	for(vector<string>::iterator it = op->begin(); (it) != op->end(); it++)
	{
		vector<string> *user = split((*it), ":");
		operatr[user->front()] = user->back();
	}
	srv.set_op(operatr);

	string host;
	getline(file, host);
	name.erase(0, 5);
	srv.set_host(host);
	

	return srv;
}

#endif