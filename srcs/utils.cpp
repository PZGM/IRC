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

void send_update(User & usr, Server & srv, string command, string params) {
    string str;
    str += ":";
    str += usr.get_nick();
    str += srv.get_code();
    str += " ";
    str += command;
    str += " ";
    str += params;
    str += "\n";
    send(str, usr.get_fd());
}

void send_update(User & usr, string command, string params) {
    string str;
    str += ":";
    str += usr.get_nick();
    str += "!~u@kq2rf7a2iqsci.irc";
    str += " ";
    str += command;
    str += " ";
    str += params;
    str += "\n";
    send(str, usr.get_fd());
}

void send_update(User & usr, Server & srv, string command, string params, int fd) {
    string str;
    str += ":";
    str += usr.get_nick();
    str += srv.get_code();
    str += " ";
    str += command;
    str += " ";
    str += params;
    str += "\n";
    send(str, fd);
}

void broadcast_update(User & usr, Server & srv, string command, string params) {
    vector<string> chans = usr.get_channels();
    list<int> fds;
    for(vector<string>::iterator it = chans.begin(); it != chans.end(); it++) {
        Channel chan = srv.get_channel_by_name(*it);
        list<User> users = chan.get_users();
        for(list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
            fds.push_back(ite->get_fd());
        }
    }
    fds.sort();
    fds.unique();
    list<int>::iterator it = fds.begin();
    while (it != fds.end()) {
        send_update(usr, srv, command, params, *it);
        it++;
    }
}

void send_msg(string msg, User &usr) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    str += msg;
    str += "\n";
    send(str, usr.get_fd());
}

void send_msg2(int num, User & usr, string msg) {
    string str = prefix(num);
    str += usr.get_nick();
    str += " ";
    str += msg;
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
    msgs[366] = "End of NAMES list";
    msgs[372] = "- +";
    msgs[375] = "- + Message of the day -";
    msgs[376] = "End of MOTD command";
    msgs[381] = "You are now an IRC operator";
    msgs[400] = "You're already opered-up!"; //Not really in the rfc2812
    msgs[421] = "Unknown command";
    msgs[431] = "No nickname given";
    msgs[432] = "Erroneous nickname";
    msgs[433] = "Nickname is already in use";
    msgs[451] = "You need to register before you can use that command";
    msgs[461] = "Not enough parameters";
    msgs[468] = "Malformed username";
    msgs[462] = "You may not reregister";
    msgs[464] = "Password incorrect";
    msgs[501] = "Unknown MODE flag";
    msgs[502] = "Cannot view/change mode for other users";
    return msgs;
}

#endif