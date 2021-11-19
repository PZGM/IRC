#include "../include/server.hpp"
      #include <sys/socket.h>
       #include <netdb.h>
void find_host(User & usr, Server & srv) {
	std::string str = ":";
	str += srv.get_name();
	str += " NOTICE * :*** Looking up your hostname...\r\n";
	send(str, usr.get_fd());
	usleep(1000000);

	str = ":";
	str += srv.get_name();
	str += " NOTICE ";
	str += usr.get_nick();
	str += " :*** Could not resolve your hostname: Request timed out; using your IP address (";
	str += usr.get_host();
	str += ") instead.\r\n";
	send(str, usr.get_fd());
}
