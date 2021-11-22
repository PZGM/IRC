#ifndef MODE_CHAN_CPP
# define MODE_CHAN_CPP

#include "../include/server.hpp"

void mode_chan(std::vector<std::string> *vec, User & usr, Server & srv) {
    std::string chan_name = (*vec)[0];
    std::string flags = (vec->size() > 1) ? (*vec)[1] : "";
    std::string nick = (vec->size() > 2) ? (*vec)[2] : "";
    int sign = 0;
    if (srv.find_channel(vec->front()) == false) {
        send_error(403, usr, vec->front(),srv);
        return;
    }
    Channel & chan = srv.get_channel_by_name(chan_name);
    if (flags != "") {
        std::list<char> lst(flags.begin(), flags.end());
        lst.sort();
        lst.unique();
        std::list<char>::iterator it = lst.begin();
        while (it != lst.end()) {
            std::string ch(1, *it);
            if (*it == '+' || *it == '-') {
                sign = (*it == '+') ? 1 : -1;
                it++;
            }
            if (*it == '+' || *it == '-')
                break;
            if (*it == 'o')
            {
                if (nick != "") {
                    if (srv.find_user(nick)){
                        if (chan.find_user(nick))
                        {
                            if (chan.is_oper(usr))
                            {
                                int to_add = srv.get_fd_from_nick(nick);
                                if (sign == 1) {
                                    chan.add_oper(to_add);
                                    send_general_update(usr, chan, "MODE " + chan_name + " +o", nick, false);
                                }
                                if (sign == -1) {
                                    chan.rm_oper(to_add);
                                    send_general_update(usr, chan, "MODE " + chan_name + " -o", nick, false);
                                }
                            }
                            else {
                                send_error(482, usr, chan_name,srv);
                                return;
                            }
                        }
                        else
                            send_error(441, usr, chan_name,srv);
                    }
                    else
                        send_error(401, usr, nick,srv);
                }
            }
            else
                send_error(472, usr, ch,srv);
            it++;
        }
    }
    send_msg2(324, usr, chan.get_name() + " " + chan.get_mode(), srv);
}

#endif
