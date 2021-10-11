#include "../include/server.hpp"

bool check_name(std::string str) {
    if (str.length() > 32)
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
    str += std::to_string(err);
    str += " ";
    str += usr.get_nick();
    str += " :";
    if (err == 431)
        str += "No nickname given";
    if (err == 432)
        str += "Erroneous nickname";
    str += "\n";
    send(str, usr.get_fd());
}

void send_error_ws(int err, User & usr, std::string msg) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    str += std::to_string(err);
    str += " ";
    str += usr.get_nick();
    str += " ";
    str += msg;
    str += " :";
    if (err == 461)
        str += "Not enough parameters";
    if (err == 432)
        str += "Erroneous nickname";
    str += "\n";
    send(str, usr.get_fd());
}