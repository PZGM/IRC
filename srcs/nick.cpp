#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr, Server & srv) {
    (void) srv;
    if (vec->front() == ":")
        vec->erase(vec->begin());
    if (vec->empty())
        send_error(431, usr);
    else {
        if (check_nick(vec->front()) == false)
            send_error(432, usr, vec->front());
        else {
            if (usr.exist())
                send_update(usr, "NICK", vec->front());
            usr.set_nick(vec->front());
        }
    }
}

#endif