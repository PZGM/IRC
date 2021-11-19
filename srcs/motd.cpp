#ifndef MOTP_CPP
# define MOTP_CPP

#include "../include/server.hpp"


void    motd(User & usr, Server & srv)
{
    send_rpl(375, usr, srv.get_name(),srv);
    std::string motd = srv.get_motd();
    if (motd.size() > 1)
    {
        std::vector<std::string> * ve = split(motd, "\\n");
        std::vector<std::string>::iterator it = ve->begin();
        while (it != ve->end()) {
            send_rpl(372, usr, *it, srv);
            it++;
        }
    }
    send_rpl(376, usr, srv);
}

#endif
