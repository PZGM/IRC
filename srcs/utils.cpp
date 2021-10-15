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

void send_error(int err, User & usr) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    if (err < 10)
        str += "0";
    if (err < 100)
        str += "0";
    str += std::to_string(err);
    str += " ";
    if (usr.is_registred())
        str += usr.get_nick();
    else
        str += "*";
    str += " :";
    if (err == 431)
        str += "No nickname given";
    if (err == 468)
        str += "Malformed username";
    if (err == 462)
        str += "You may not reregister";
    str += "\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, string str1) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    if (rpl < 10)
        str += "0";
    if (rpl < 100)
        str += "0";
    str += std::to_string(rpl);
    str += " ";
    if (usr.is_registred())
        str += usr.get_nick();
    else
        str += "*";
    str += " :";
    if (rpl == 1) {
        str += "Welcome to the Internet Relay Network ";
        str += usr.get_nick();
    }
    if (rpl == 2) {
        str += "Your host is ";
        str += SERVER_NAME;
        str += ", running version ";
        str += SERVER_VERSION;
    }
    if (rpl == 3) {
        str += "This server was created ";
        str += str1;
    }
    if (rpl == 4) {
        str += SERVER_NAME;
        str += " ";
        str += SERVER_VERSION;
        str += " BERTZios CEIMRUabefhiklmnoqstuv Iabefhkloqv";
    }
    str += "\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr, std::string msg) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    if (err < 10)
        str += "0";
    if (err < 100)
        str += "0";
    str += std::to_string(err);
    str += " ";
    if (usr.is_registred())
        str += usr.get_nick();
    else
        str += "*";
    str += " ";
    str += msg;
    str += " :";
    if (err == 461)
        str += "Not enough parameters";
    if (err == 432)
        str += "Erroneous nickname";
    if (err == 421)
        str += "Unknown command";
    if (err == 433)
        str += "Nickname is already in use";
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