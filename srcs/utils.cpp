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

bool check_nick(std::string str) {
    if (str.length() > 9)
        return false;
    std::string::iterator it = str.begin();
    if (!check_char(true, false, true, "", *it)) 
        return false;
    it++;
    while (it != str.end()) {
        if (!check_char(true, true, true, "-", *it))
            return false;
        it++;
    }
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
    str += std::to_string(err);
    str += " ";
    if (usr.isRegistred())
        str += usr.getNick();
    else
        str += "*";
    str += " :";
    if (err == 431)
        str += "No nickname given";
    str += "\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr, std::string msg) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    str += std::to_string(err);
    str += " ";
    if (usr.isRegistred())
        str += usr.getNick();
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
    str += "\n";
    send(str, usr.get_fd());
}

void send_update(User & usr, std::string command, std::string params) {
    std::string str;
    str += ":";
    str += usr.getNick();
    str += "!~u@kq2rf7a2iqsci.irc";
    str += " ";
    str += command;
    str += " :";
    str += params;
    str += "\n";
    send(str, usr.get_fd());
}