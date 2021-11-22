#ifndef PARSING_CPP
# define PARSING_CPP

#include "../include/server.hpp"


std::vector<std::string> * split(std::string str, std::string sep) {
	std::vector<std::string> * ret = new std::vector<std::string>();
	int i = 0;
	while (1) {
		if (str.length() == 0)
			return ret;
		while (str.find(sep) == 0)
			str.erase(0, sep.length());
		i = str.find(sep);
		if (i == -1) {
			while (str.find(sep) == 0)
				str.erase(0, sep.length());
			if (str.length() != 0)
				ret->insert(ret->end(), str);
			return ret;
		}
		ret->insert(ret->end(), str.substr(0, i));
		str.erase(0, i);
	}
	return (ret);
}


void parsing(std::string str, User & usr, Server & srv) {
	//std::cout << "< " << str << std::endl;
    std::map<std::string, void(*)(std::vector<std::string>*, User &,Server &)> fmap;
	fmap["JOIN"] = join;
	fmap["USER"] = user;
	fmap["NICK"] = nick;
	fmap["PRIVMSG"] = privmsg;
	fmap["NOTICE"] = notice;
	fmap["OPER"] = oper;
	fmap["MODE"] = mode;
	fmap["PING"] = ping;
	fmap["PONG"] = pong;
	fmap["WHO"]  = who;
	// fmap["PART"] = part;
	fmap["QUIT"] = quit;
	fmap["CAP"] = cap;
	fmap["WHOIS"] = whois;

	if (str[str.length() -1] == '\n')
		str.resize(str.length() - 1);
	if (str[str.length() -1] == 13)
		str.resize(str.length() - 1);
	if (str.size() == 0)
		return;
	std::vector<std::string> *vec = split(str, " ");
	std::string command = allupper(vec->front());
	if (command.empty())
		return;
	if (fmap.count(command)) {
		if (!usr.is_registred() && (command == "JOIN" || command == "PRIVMSG" || command == "OPER")) {
			send_error(451, usr,srv);
			return;
		}
		vec->erase(vec->begin());
		if (vec->size() == 0) {
			send_error(461, usr, command,srv);
			return;
		}
		fmap[command](vec, usr, srv);
	}
	else if (command == "MOTD")
		motd(usr, srv);
	else if (command == "PART")
	{
		vec->erase(vec->begin());
		vec->push_back(":");
		part(vec, usr, srv);
	}
	else
		send_error(421, usr, command,srv);
}


#endif
