#ifndef USER_CPP
# define USER_CPP

# include "../include/server.hpp"

// bool verif(string str)
// {
// 	if (s)
// }

void user(vector<string> *vec, User & usr, Server & srv) {
	(void)srv;
	if (vec->size() < 4) {
		send_error(461, usr, "USER");
		return;
	}
	if (check_user_name(vec->front()) == false)
		send_error(468, usr);
	usr.set_user(vec->front());
	vec->erase(vec->begin(), vec->begin() + 3);
	string str = vec->front();
	vec->erase(vec->begin());
	while (vec->size() != 0) {
		str += " ";
		str += vec->front();
		vec->erase(vec->begin());
	}
	usr.setRealName(str);
	if (usr.getNick() != "")
		registerUser(usr);
}

#endif