#ifndef CONF_CPP
# define CONF_CPP

#include "../include/server.hpp"


Server	configure(char *path)
{
	std::ifstream file(path);
	
	std::string port;
	getline(file, port);
	if (port.find("PORT=") == std::string::npos)
	{
		std::cout << "Error port in conf file" << std::endl;
		exit(0);
	}
	port.erase(0, 5);
	
	std::string mdp;
	getline(file, mdp);
	if (mdp.find("PASS=") == std::string::npos)
	{
		std::cout << "No password in conf file" << std::endl;
		exit(0);
	}
	mdp.erase(0, 5);
	
	Server srv(port, mdp);
	
	std::string motd;
	getline(file, motd);
	if (motd.find("MOTD=") == std::string::npos)
	{
		std::cout << "No message of the day in conf file" << std::endl;
		exit(0);
	}
	motd.erase(0, 6);
	motd.resize(motd.length() - 1);
	srv.set_motd(motd);
	
	std::string name;
	getline(file, name);
	if (name.find("NAME=") == std::string::npos)
	{
		std::cout << "No name in conf file" << std::endl;
		exit(0);
	}
	name.erase(0, 5);
	srv.set_name(name);

	std::string oper;
	getline(file, oper);
	if (oper.find("OPER=") == std::string::npos)
	{
		std::cout << "No operator in conf file" << std::endl;
		exit(0);
	}
	oper.erase(0, 6);
	oper.resize(oper.length() - 1);
	std::vector<std::string> *op = split(oper, "|");
	std::map<std::string, std::string> operatr;
	for(std::vector<std::string>::iterator it = op->begin(); (it) != op->end(); it++)
	{
		std::vector<std::string> *user = split((*it), ":");
		operatr[user->front()] = user->back();
	}
	srv.set_op(operatr);

	std::string host;
	getline(file, host);
	if (host.find("HOST=") == std::string::npos)
	{
		std::cout << "No host in conf file" << std::endl;
		exit(0);
	}
	host.erase(0, 6);
	host.resize(host.length() - 1); 
	srv.set_host(host);
	
	return srv;
}

#endif