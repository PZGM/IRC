#include "server.hpp"

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

void parsing(std::string str) {
    vector<string> *vec = split(str, " ");
    string command = allupper(vec->front());
    if (command == "JOIN") {
        std::cout << "join" << std::endl;
    }
    else if (command == "USER") {
        std::cout << "USER" << std::endl;
    }
    else if (command == "NICK") {
        std::cout << "NICK" << std::endl;
    }
    else if (command == "PRIVMSG") {
        std::cout << "private msg" << std::endl;
    }
    else if (command == "OPER") {
        std::cout << "oper" << std::endl;
    }
    else if (command == "MODE") {
        std::cout << "mode" << std::endl;
    }
    else
        std::cout << "command not found" << std::endl;
}
