#ifndef USER_CPP
# define USER_CPP

# include "../include/server.hpp"

void user(std::vector<std::string> *vec, User & usr, Server & srv) {
	(void)srv;
	if (vec->size() < 4) {
		send_error(461, usr, "USER");
		return;
	}
	if (usr.is_registred() == true) {
		send_error(462, usr);
		return;
	}
	if (check_user_name(vec->front()) == false) {
		send_error(468, usr);
		return;
	}
	usr.set_user(vec->front());
	vec->erase(vec->begin(), vec->begin() + 3);
	std::string str = vec->front();
	vec->erase(vec->begin());
	while (vec->size() != 0) {
		str += " ";
		str += vec->front();
		vec->erase(vec->begin());
	}
	if (str[0] == ':')
		str.erase(0, 1);
	usr.set_real_name(str);
	if (usr.get_nick() != "") {
		register_user(usr, srv);
	}
}

#endif
