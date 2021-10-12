#ifndef REGISTRATION_CPP
# define REGISTRATION_CPP

#include "../include/server.hpp"

bool registerUser(User & usr) {
    if (check_nick(usr.getNick()) == false) {
        send_error(432, usr, usr.getNick());
        return false;
    }
    usr.setRegistred(true);
    return true;
}

#endif