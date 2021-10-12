#ifndef REGISTRATION_CPP
# define REGISTRATION_CPP

#include "../include/server.hpp"

bool register_user(User & usr) {
    if (check_nick(usr.get_nick()) == false) {
        send_error(432, usr, usr.get_nick());
        return false;
    }
    usr.set_registred(true);
    return true;
}

#endif