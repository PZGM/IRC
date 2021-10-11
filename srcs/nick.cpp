#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr, Server & srv) {
    (void) srv;
    if (vec->empty())
        send_error(431, usr);
    else {
        if (check_name(vec->front()) == false)
            send_error_ws(432, usr, vec->front());
        else {
            usr.set_nick(vec->front());
            //send response
        }
    }
}

#endif