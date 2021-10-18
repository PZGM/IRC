#ifndef MODE_CHAN_CPP
# define MODE_CHAN_CPP

#include "../include/server.hpp"

void mode_chan(vector<string> *vec, User & usr, Server & srv) {
    if (srv.find_channel(vec->front()) == false) {
        send_error(403, usr, vec->front());
        return;
    }
    Channel & chan = srv.get_channel_by_name(vec->front());
    send_msg2(324, usr, chan.get_name() + " " + chan.get_mode());
}

#endif