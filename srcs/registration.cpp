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
    send_rpl(1, usr, usr.get_nick());
    send_rpl(2, usr, SERVER_NAME, SERVER_VERSION);
    send_rpl(3, usr, srv.get_creation_time());
    send_rpl(4, usr, SERVER_NAME, SERVER_VERSION);
    send_rpl(375, usr, SERVER_NAME);
    string motd = srv.get_motd();
    vector<string> * vec = split(motd, "\\n");
    vector<string>::iterator it = vec->begin();
    while (it != vec->end()) {
        send_rpl(372, usr, *it);
        it++;
    }
    send_rpl(376, usr);
    return true;
}

#endif