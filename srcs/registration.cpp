#ifndef REGISTRATION_CPP
# define REGISTRATION_CPP

#include "../include/server.hpp"

bool register_user(User & usr, Server & srv) {
    string nick = usr.get_nick();
    if (check_nick(nick) == false) {
        send_error(432, usr, nick);
        return false;
    }
    if (check_nick_availibility(nick, srv) == false) {
        send_error(433, usr, nick);
        return false;
    }
    usr.set_registred(true);
    send("=====> YOU'RE REGISTRED !\n", usr.get_fd());
    return true;
}

#endif