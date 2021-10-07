#ifndef USER_CPP
# define USER_CPP

# include "server.hpp"

void user(vector<string> *vec, User & usr) {
    if (vec->size() < 4)
        std::cout << "wrong format" << std::endl;
    else {
        vector<string>::iterator it = vec->begin();
        std::cout << *it << std::endl;
        if (usr.set_user(*it++))
            cout<<"user good"<<endl;
        std::cout << *it << std::endl;
        if (usr.set_flags(*it++))
            cout<<"flag good"<<endl;
        std::cout << *it << std::endl;
        it++;
        std::cout << *it << std::endl;
        while ()
        if (usr.set_real(*it))
            cout<<"real good"<<endl;
    }

}

#endif