#ifndef PONG_CPP
# define PONG_CPP

#include "../include/server.hpp"

void ping(std::vector<std::string> *vec, User & usr, Server & srv) {
    (void)usr;
    (void)srv;
    std::string str = ":";
    str += SERVER_NAME;
    str += " PONG ";
    str += SERVER_NAME;
    str += " :";
    str += vec->front();
	str += "\r\n";
    send(str, usr.get_fd());
}

void pong(std::vector<std::string> *vec, User & usr, Server & srv) {
    (void)usr;
    (void)srv;
    std::vector<std::string>::iterator it = vec->begin();
    while (it != vec->end()) {
        it++;
    }
}

#endif
