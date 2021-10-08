#ifndef NICK_CPP
# define NICK_CPP

#include "../include/server.hpp"

void nick(vector<string> *vec, User & usr) {
    if (vec->empty())
        std::cout << "wrong format" << std::endl;
    else {
        if (usr.set_nick(vec->front()))
            std::cout << "nick changed" << std::endl;
        else
            std::cout << "nick not changed" << std::endl;
    }
}

#endif