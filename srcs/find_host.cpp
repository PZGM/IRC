#include "../include/server.hpp"

void find_host(User & usr) {
	string str += ":";
	str = SERVER_NAME;
	str += " NOTICE * :*** Looking up your hostname...";
	send(str, usr.get_fd());
	usleep(100000);
	str += ":";
	str = SERVER_NAME;
	str += " NOTICE ";
	str += usr.get_nick();
	str += " :*** Could not resolve your hostname: Request timed out; using your IP address (";
	str += usr.get_host();
	str += ") instead.";
	send(str, usr.get_fd());
}
