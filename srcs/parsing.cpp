#ifndef PARSING_CPP
# define PARSING_CPP

#include "../include/server.hpp"


vector<string> * split(string str, string sep) {
	vector<string> * ret = new vector<string>();
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
	std::cout << "< " << str << std::endl;
    map<string,void(*)(vector<string>*, User &,Server &)> fmap;
	fmap["JOIN"] = join;
	fmap["USER"] = user;
	fmap["NICK"] = nick;
	fmap["PRIVMSG"] = privmsg;
	fmap["OPER"] = oper;
	fmap["MODE"] = mode;
	fmap["PING"] = ping;
	fmap["PONG"] = pong;
	fmap["WHO"]  = who;
	fmap["PART"] = part;
	fmap["QUIT"] = quit;
	fmap["CAP"] = cap;
	fmap["WHOIS"] = whois;

	if (str[str.length() -1] == '\n')
		str.resize(str.length() - 1);
	if (str[str.length() -1] == 13)
		str.resize(str.length() - 1);
	if (str.size() == 0)
		return;
	vector<string> *vec = split(str, " ");
	string command = allupper(vec->front());
	if (command.empty())
		return;
	if (fmap.count(command)) {
		if (!usr.is_registred() && (command == "JOIN" || command == "PRIVMSG" || command == "OPER")) {
			send_error(451, usr);
			return;
		}
		vec->erase(vec->begin());
		if (vec->size() == 0) {
			send_error(461, usr, command);
			return;
		}
		fmap[command](vec, usr, srv);
	}
	else
		send_error(421, usr, command);
}


#endif
