#ifndef UTILS_CPP
# define UTILS_CPP


#include "../include/server.hpp"

string  get_user_prefix(User usr, Server srv) {
	string str = ":";
	str += usr.get_nick();
	str += "!";
	str += usr.get_real_name();
	str += "@";
	str += srv.get_host();
	return str;
}

void    send_update(User & usr, Server & srv, string cmd, string args, int fd) {
    string str = get_user_prefix(usr, srv);
	str += " " + cmd + " :" + args + "\r\n";
    send(str, fd);    
}

void    send_general_update(User & usr, Server & srv, Channel & chan, string cmd, string args, bool exclude_sender) {
    list<User> userList = chan.get_users();
    for (list<User>::iterator it = userList.begin(); it != userList.end(); it++)
    {
    	if (!exclude_sender || (*it).get_fd() != usr.get_fd())
    		send_update(usr, srv, cmd, args, it->get_fd());
    }
}

void broadcast_update(User & usr, Server & srv, string command, string params) {
    vector<string> chans = usr.get_channels();
    list<int> fds;
    fds.push_back(usr.get_fd());
    for(vector<string>::iterator it = chans.begin(); it != chans.end(); it++) {
        Channel chan = srv.get_channel_by_name(*it);
        list<User> users = chan.get_users();
        for(list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
            fds.push_back(ite->get_fd());
        }
    }
    fds.sort();
    fds.unique();
    list<int>::iterator it = fds.begin();
    while (it != fds.end()) {
        send_update(usr, srv, command, params, *it);
        it++;
    }
}
// :gg       ! g                      @127.0.0.1 PRIVMSG ff       :slt connard
// :afreire-_!:Adrien FREIRE ELEUTERIO@127.0.0.1 PRIVMSG afreire- ::yo
bool check_char(bool alpha, bool digit, bool special, std::string more, char c) {
    if (alpha && ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        return true;
    if (digit && c >= '0' && c <= '9')
        return true;
    if (special && ((c >= '[' && c <= '`') || (c >= '{' && c <= '}')))
        return true;
    if (more.find(c) != std::string::npos)
        return true;
    return false;
}

bool check_nick_availibility(std::string str, Server & srv) {
    map<int, User> & users = srv.get_users();
    map<int, User>::iterator it = users.begin();
    while (it != users.end()) {
        User & usr = (*it).second;
        if (usr.get_nick() == str && usr.is_registred())
            return false;
        it++;
    }
    return true;
}

bool check_nick(std::string str) {
    if (str.length() > 9)
        return false;
    std::string::iterator it = str.begin();
    if (!check_char(true, false, true, "", *it)) 
        return false;
    it++;
    while (it != str.end()) {
        if (!check_char(true, true, true, "-", *it))
            return false;
        it++;
    }
    return true;
}

bool check_user_name(std::string str) {
    if (str.find('@') != std::string::npos || str.find(' ') != std::string::npos)
        return false;
    return true;
}


void send(std::string str, int fd) { 
    std::cout << "> " << str << std::endl;
    send(fd, str.c_str(), str.length(), 0);
}

//

void send_rpl(int rpl, User & usr) {
    map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, string s1) {
    map<int, std::string> msgs = get_msgs();
    std::string str = prefix(rpl);
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[rpl];
    str.replace(str.find("+"), 1, s1);
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_rpl(int rpl, User & usr, string s1, string s2) {
    std::string str = prefix(rpl);
    map<int, std::string> msgs = get_msgs();
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
    map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " :";
    str += msgs[err];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_error(int err, User & usr, std::string ctx) {
    std::string str = prefix(err);
    map<int, std::string> msgs = get_msgs();
    str += (usr.is_registred()) ? usr.get_nick() : "*";
    str += " ";
    str += ctx;
    str += " :";
    str += msgs[err];
    str += "\r\n";
    send(str, usr.get_fd());
}

void send_privmsg(User & usr, Server & srv, string command, string params, int fd) {
    string str;
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

void send_who(User & usr, string chan_name,User & us, Server srv) {
    string str = prefix(352);
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
	vector<string>  coco;
	string str = prefix(311);
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
		for(vector<string>::iterator it = coco.begin(); it != coco.end(); it++)
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

    send(str, usr.get_fd());
	send_error(318, tom);
}

void send_msg(string msg, User &usr) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    str += msg;
    str += "\n";
    send(str, usr.get_fd());
}

void send_msg2(int num, User & usr, string msg) {
    string str = prefix(num);
    str += usr.get_nick();
    str += " ";
    str += msg;
    str += "\n";
    send(str, usr.get_fd());
}

string prefix(int num) {
    std::string str;
    str += ":";
    str += SERVER_NAME;
    str += " ";
    if (num < 10)
        str += "0";
    if (num < 100)
        str += "0";
    str += std::to_string(num);
    str += " ";
    return str;
}

map<int, string> get_msgs(void) {
    map<int, string> msgs;
    msgs[1]   = "Welcome to the Internet Relay Network +";
    msgs[2]   = "Your host is +, running version +";
    msgs[3]   = "This server was created +";
    msgs[4]   = "+ + BERTZios CEIMRUabefhiklmnoqstuv Iabefhkloqv";
    msgs[315] = "End of /WHO list";
	msgs[318] = "End of /WHOIS list";
    msgs[366] = "End of NAMES list";
    msgs[372] = "- +";
    msgs[375] = "- + Message of the day -";
    msgs[376] = "End of MOTD command";
    msgs[381] = "You are now an IRC operator";
    msgs[400] = "You're already opered-up!"; //Not really in the rfc2812
    msgs[401] = "No such nick";
    msgs[403] = "No such channel";
    msgs[421] = "Unknown command";
    msgs[431] = "No nickname given";
    msgs[432] = "Erroneous nickname";
    msgs[433] = "Nickname is already in use";
    msgs[441] = "They aren't on that channel";
    msgs[451] = "You need to register before you can use that command";
    msgs[461] = "Not enough parameters";
    msgs[468] = "Malformed username";
    msgs[462] = "You may not reregister";
    msgs[464] = "Password incorrect";
    msgs[472] = "is unknown mode char to me"; //en vrai ca devrait etre un peu plus long mais chuuuutttt
    msgs[476] = "Invalid channel name";
    msgs[482] = "You're not a channel operator";
    msgs[501] = "Unknown MODE flag";
    msgs[502] = "Cannot view/change mode for other users";
    return msgs;
}

#endif
