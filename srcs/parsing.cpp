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


void	yo(int i)
{
	std::cout << "yo = " << i << std::endl;
}
void	mdr(int i)
{
	std::cout << "mdr = " << i << std::endl;
}


// ======================================================================================================
// IL FAUT TOUT METTRE DANS LA CLASSE SERVER CAR JOIN UTILISE PAS LE USER 
// ======================================================================================================
void parsing(std::string str, User & usr) {
	Server server;
    map<string,void(*)(vector<string>*, User &,Server &)> fmap;
	fmap["NICK"] = nick;




	usr.print();
	if (str[str.length() -1] == '\n')
		str.resize(str.length() - 1);
	if (str.size() == 0)
		return;
	vector<string> *vec = split(str, " ");
	string command = allupper(vec->front());
	if (command.empty())
		return;
	vec->erase(vec->begin());
	if (command == "JOIN") {
		std::cout << "___Command: JOIN" << std::endl;
		// join(vec[0], srv); 
	}
	else if (command == "USER") {
		std::cout << "___Command: USER" << std::endl;
		user(vec, usr,server);
	}
	else if (command == "NICK") {
		std::cout << "___Command: NICK" << std::endl;
		fmap["NICK"](vec, usr, server);
		// nick(vec, usr, server);
	}
	else if (command == "PRIVMSG") {
		std::cout << "___Command: PRIVMSG" << std::endl;
	}
	else if (command == "OPER") {
		std::cout << "___Command: OPER" << std::endl;
	}
	else if (command == "MODE") {
		std::cout << "___Command: MODE" << std::endl;
	}
	else
		std::cout << "command not found" << std::endl;
}


#endif
