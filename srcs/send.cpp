#include "../include/server.hpp"

void send(std::string str, int fd) { 
    std::cout << "> " << str << std::endl;
    send(fd, str.c_str(), str.length(), 0);
}

void    send_update(User & usr, Server & srv, std::string cmd, std::string args, int fd) {
    std::string str = get_user_prefix(usr, srv);
	str += " " + cmd + " :" + args + "\r\n";
    send(str, fd);    
}

void    send_general_update(User & usr, Server & srv, Channel & chan, std::string cmd, std::string args, bool exclude_sender) {
    std::list<User> userList = chan.get_users();
    for (std::list<User>::iterator it = userList.begin(); it != userList.end(); it++)
    {
    	if (!exclude_sender || (*it).get_fd() != usr.get_fd())
    		send_update(usr, srv, cmd, args, it->get_fd());
    }
}


void send_rpl(int rpl, User & usr) {
    std::map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, std::string s1) {
    std::map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str.replace(str.find("+"), 1, s1);
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, std::string s1, std::string s2) {
    std::string str = prefix(rpl);
    std::map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str.replace(str.find("+"), 1, s1);
    str.replace(str.find("+"), 1, s2);
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr) {
    std::string str = prefix(err);
    std::map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[err];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr, std::string ctx) {
    std::string str = prefix(err);
    std::map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " ";
    str += ctx;
    str += " :";
    str += msgs[err];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_privmsg(User & usr, Server & srv, std::string command, std::string params, int fd) {
    std::string str;
    str += get_user_prefix(usr, srv);
    str += " ";
    str += command;
    str += " ";
    str += srv.get_nick_from_fd(fd);
    str += " :";
    str += params;
    str += "\r\n";
    send(str, fd);
}

void send_who(User & usr, std::string chan_name, User & us, Server srv) {
    std::string str = prefix(352);
	str += us.get_nick();
	str += " ";
	str += chan_name;
	str += " ";
	str += us.get_real_name();
	str += " ";
	str += srv.get_host();
    str += " ";
    str += SERVER_NAME;
	str += " ";
    str += us.get_nick();
    str += " ";
    str += "H";
    if (us.is_oper() == true)
        str += "@";
    str += " :0 ";
    str += us.get_real_name();
    str += "\r\n";

    send(str, usr.get_fd());
}

void send_whois(User & usr, User & tom, Server srv)
{
	std::vector<std::string>  coco;
	std::string str = prefix(311);
	str += tom.get_nick();
	str += " ";
	str += tom.get_real_name();
	str += " ";
	str += srv.get_host();
    str += " ";
    str += SERVER_NAME;
    str += " ";
    str += "*";
    str += " :";
    str += tom.get_real_name();
    str += "\r\n";
	str += prefix(378);
	str += usr.get_nick();
	str += " ";
	str += tom.get_nick();
	str += " :is connecting from ";
	str += tom.get_real_name();
	str += "@";
	str += srv.get_host();
	str += " ";
	str += srv.get_host();
	str += "\r\n";
	if(!tom.get_channels().empty())
	{
		coco = tom.get_channels();
		str += prefix(319);
		str += usr.get_nick();
		str += " ";
		str += " :";
		for(std::vector<std::string>::iterator it = coco.begin(); it != coco.end(); it++)
		{
			str += ((srv.get_channel_by_name(*it).is_oper(tom)) ? "@" : "");
			str += *it;
			str += " ";
		}
		str += "\r\n";
	}
	str += prefix(312);
	str += usr.get_nick();
	str += " ";
	str += tom.get_nick();
	str += " ";
	str += SERVER_NAME;
	str += " :Local ";
	str += "IRC Server";
	str += "\r\n";
	str += prefix(379);
	str += usr.get_nick();
	str += " ";
	str += tom.get_nick();
	str += " :is using modes +";
	str += (tom.is_oper() ? "o" : "");
	str += (tom.get_inv() ? "i" : "");
	str += "\r\n";
	str += prefix(317);
	str += usr.get_nick();
	str += " ";
	str += tom.get_nick();
	str += " ";
	str += std::to_string(time(0) - tom.get_last_activity());
	str += " ";
	str += std::to_string(tom.get_last_connection());
	str += " :seconds idle, signon time";
	str += "\r\n";

    send(str, usr.get_fd());
	send_error(318, tom);
}

void send_msg(std::string msg, User &usr) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    str += msg;
    str += "\n";
    send(str, usr.get_fd());
}

void send_msg2(int num, User & usr, std::string msg) {
    std::string str = prefix(num);
    str += usr.get_nick();
    str += " ";
    str += msg;
    str += "\n";
    send(str, usr.get_fd());
}
