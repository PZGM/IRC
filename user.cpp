#ifndef USER_CPP
# define USER_CPP

# include "server.hpp"

void user(vector<string> *vec, User & usr) {
    if (vec->size() != 4)
        std::cout << "wrong format" << std::endl;
    else {
        vector<string>::iterator it = vec->begin();
        if (usr.set_user(*it++))
            cout<<"user good"<<endl;
        if (usr.set_flag(*it++))
            cout<<"flag good"<<endl;
        it++;
        if (usr.set_real(*it))
            cout<<"real good"<<endl;
    }

}

#endif