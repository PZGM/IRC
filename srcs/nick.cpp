#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr, Server & srv) {
    (void) srv;
    if (vec->front() == ":")
        vec->erase(vec->begin());
    if (vec->empty() == false && usr.get_real_name() == "") {
        usr.set_nick(vec->front());
        return;
    }
    if (vec->empty()) {
        send_error(431, usr);
        return;
    }
    if (check_nick(vec->front()) == false) {
        send_error(432, usr, vec->front());
        return;
    }
    if (check_nick_availibility(vec->front(), srv) == false) {
        send_error(433, usr, vec->front());
        return;
    }
    if (usr.is_registred())
        send_update(usr, "NICK", vec->front());
    usr.set_nick(vec->front());
    if (!usr.is_registred())
        register_user(usr);
}

#endif