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


<<<<<<< HEAD
void parsing(std::string str, User & usr) {
	Server server;
=======
// ======================================================================================================
// IL FAUT TOUT METTRE DANS LA CLASSE SERVER CAR JOIN UTILISE PAS LE USER 
// ======================================================================================================
void parsing(std::string str, User & usr, Server & srv) {
>>>>>>> 465ad86209de3700d9f39c6b01da0f2227ac08b5
    map<string,void(*)(vector<string>*, User &,Server &)> fmap;
	fmap["JOIN"] = join;
	fmap["USER"] = user;
	fmap["NICK"] = nick;
	fmap["PRIVMSG"] = privmsg;
	fmap["OPER"] = oper;
	fmap["MODE"] = mode;



	usr.print();
	if (str[str.length() -1] == '\n')
		str.resize(str.length() - 1);
	if (str.size() == 0)
		return;
	vector<string> *vec = split(str, " ");
	string command = allupper(vec->front());
	if (command.empty())
		return;
	if (fmap.count(command)) {
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