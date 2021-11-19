#ifndef REGISTRATION_CPP
# define REGISTRATION_CPP

#include "../include/server.hpp"

bool register_user(User & usr, Server & srv) {
	std::cout << "Registration" << std::endl;
    std::string nick = usr.get_nick();
    if (check_nick(nick) == false) {
        send_error(432, usr, nick,srv);
        return false;
    }
    if (check_nick_availibility(nick, srv) == false) {
        send_error(433, usr, nick,srv);
        return false;
    }
    usr.set_registred(true);
    usr.set_log(time(0));
    send_rpl(1, usr, usr.get_nick(), srv);
    send_rpl(2, usr, srv.get_name(), SERVER_VERSION, srv);
    send_rpl(3, usr, srv.get_creation_time(), srv);
    send_rpl(4, usr, srv.get_name(), SERVER_VERSION, srv);
    send_rpl(375, usr, srv.get_name(),srv);
    std::string motd = srv.get_motd();
    std::vector<std::string> * vec = split(motd, "\\n");
    std::vector<std::string>::iterator it = vec->begin();
    while (it != vec->end()) {
        send_rpl(372, usr, *it, srv);
        it++;
    }
    send_rpl(376, usr, srv);
	find_host(usr, srv);
    return true;
}

#endif
