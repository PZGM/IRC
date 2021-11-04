#ifndef PONG_CPP
# define PONG_CPP

#include "../include/server.hpp"

void ping(vector<string> *vec, User & usr, Server & srv) {
    (void)usr;
    (void)srv;
    string str = ":";
    str += SERVER_NAME;
    str += " PONG ";
    str += SERVER_NAME;
    str += " ";
    str += vec->front();
    send(str, usr.get_fd());
}

void pong(vector<string> *vec, User & usr, Server & srv) {
    (void)usr;
    (void)srv;
    vector<string>::iterator it = vec->begin();
    while (it != vec->end()) {
        it++;
    }
}

#endif