#ifndef UTILS_CPP
# define UTILS_CPP


#include "../include/server.hpp"

bool check_char(bool alpha, bool digit, bool special, std::string more, char c) {
    if (alpha && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        return true;
    if (digit && c >= '0' && c <= '9')
        return true;
    if (special && ((c >= '[' && c <= '`') || (c >= '{' && c <= '}')))
        return true;
    if (more.find(c) != std::string::npos)
        return true;
    return false;
}

bool check_nick_availibility(std::string str, Server & srv) {
    map<int, User> & users = srv.get_users();
    map<int, User>::iterator it = users.begin();
    while (it != users.end()) {
        User & usr = (*it).second;
        if (usr.get_nick() == str && usr.is_registred())
            return false;
        it++;
    }
    return true;
}

bool check_nick(std::string str) {
    if (str.length() > 9)
        return false;
    std::string::iterator it = str.begin();
    if (!check_char(true, false, true, "", *it)) 
        return false;
    it++;
    while (it != str.end()) {
        std::cout << "." << std::endl;
        if (!check_char(true, true, true, "-", *it))
            return false;
        it++;
    }
    return true;
}

bool check_user_name(std::string str) {
    if (str.find('@') != std::string::npos || str.find(' ') != std::string::npos)
        return false;
    return true;
}


void send(std::string str, int fd) {
    std::cout << "[" << fd << "] => " << str << std::endl;
    send(fd, str.c_str(), str.length(), 0);
}

void send_rpl(int rpl, User & usr) {
    map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str += "\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, string s1) {
    map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str.replace(str.find("+"), 1, s1);
    str += "\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, string s1, string s2) {
    std::string str = prefix(rpl);
    map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str.replace(str.find("+"), 1, s1);
    str.replace(str.find("+"), 1, s2);
    str += "\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr) {
    std::string str = prefix(err);
    map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[err];
    str += "\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr, std::string ctx) {
    std::string str = prefix(err);
    map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " ";
    str += ctx;
    str += " :";
    str += msgs[err];
    str += "\n";
    send(str, usr.get_fd());
}

void send_update(User & usr, std::string command, std::string params) {
    std::string str;
    str += ":";
    str += usr.get_nick();
    str += "!~u@kq2rf7a2iqsci.irc";
    str += " ";
    str += command;
    str += " :";
    str += params;
    str += "\n";
    send(str, usr.get_fd());
}

string prefix(int num) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    if (num < 10)
        str += "0";
    if (num < 100)
        str += "0";
    str += std::to_string(num);
    str += " ";
    return str;
}

map<int, string> get_msgs(void) {
    map<int, string> msgs;
    msgs[1]   = "Welcome to the Internet Relay Network +";
    msgs[2]   = "Your host is +, running version +";
    msgs[3]   = "This server was created +";
    msgs[4]   = "+ + BERTZios CEIMRUabefhiklmnoqstuv Iabefhkloqv";
    msgs[372] = "- +";
    msgs[375] = "- + Message of the day -";
    msgs[376] = "End of MOTD command";
    msgs[421] = "Unknown command";
    msgs[431] = "No nickname given";
    msgs[432] = "Erroneous nickname";
    msgs[433] = "Nickname is already in use";
    msgs[461] = "Not enough parameters";
    msgs[468] = "Malformed username";
    msgs[462] = "You may not reregister";
    return msgs;
}

// Channel * get_chan_by_name(Server &srv, string name) {
//     map<string, Channel>::iterator it = srv.get_begin_channel();
//     while (it != srv.get_end_channel()) {
//         if (it->first == name) {
//             return it->second;
//         }
//         it++;
//     }
// }

// list<User> get_chans_usrs(User & usr, Server & srv) {
//     list<User> users;
//     list<string> chans = usr.get_chans();
//     list<string>::iterator it = chans.begin();
//     while (it != chans.end()) {
//         Channel * chan = get_chan_by_name(*it);
//         users.insert(chan->get_users().begin(), chan->get_users().end());
//         it++;
//     }
//     users.unique();
//     list<User>::iterator ite = users.begin();
//     std::cout << "=======" << std::endl;
//     while (ite != users.end()) {
//         std::cout << ite->get_nick() << std::endl;
//     }
//     std::cout << "=======" << std::endl;
//     return users;
// }

#endif