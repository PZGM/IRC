#include "../include/server.hpp"

void check_timeout(User & usr, Server srv) {
	if (!usr.is_registred())
		return;
	std::cout << "Check" << std::endl;
	if (time(0) - usr.get_last_ping() > srv.get_time_out() / 2 && usr.get_waiting_for_pong() == false) {
		std::string str = "PING ";
		str += SERVER_NAME;
		send(str, usr.get_fd());
		usr.set_waiting_for_pong(true);
	}	
	if (time(0) - usr.get_last_ping() > srv.get_time_out()) {
		std::string str = "ERROR :Closing link: (";
		str += usr.get_real_name();
		str += "@";
		str += srv.get_host();
		str += ") [Ping timeout: ";
		str += srv.get_time_out();
		str += " seconds]";
	}
}
