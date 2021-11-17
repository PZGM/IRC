#ifndef REGISTRATION_CPP
# define REGISTRATION_CPP

#include "../include/server.hpp"

bool register_user(User & usr, Server & srv) {
	std::cout << "Registration" << std::endl;
    std::string nick = usr.get_nick();
    if (check_nick(nick) == false) {
        send_error(432, usr, nick);
        return false;
    }
    if (check_nick_availibility(nick, srv) == false) {
        send_error(433, usr, nick);
        return false;
    }
    usr.set_registred(true);
    usr.set_log(time(0));
    send_rpl(1, usr, usr.get_nick());
    send_rpl(2, usr, SERVER_NAME, SERVER_VERSION);
    send_rpl(3, usr, srv.get_creation_time());
    send_rpl(4, usr, SERVER_NAME, SERVER_VERSION);
    send_rpl(375, usr, SERVER_NAME);
    std::string motd = srv.get_motd();
    std::vector<std::string> * vec = split(motd, "\\n");
    std::vector<std::string>::iterator it = vec->begin();
    while (it != vec->end()) {
        send_rpl(372, usr, *it);
        it++;
    }
    send_rpl(376, usr);
	find_host(usr);
    return true;
}

#endif
