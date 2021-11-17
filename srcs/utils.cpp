#include "../include/server.hpp"

std::string  get_user_prefix(User usr) {
	std::string str = ":";
	str += usr.get_nick();
	str += "!";
	str += usr.get_real_name();
	str += "@";
	str += usr.get_host();
	return str;
}

void broadcast_update(User & usr, Server & srv, std::string command, std::string params) {
    std::vector<std::string> chans = usr.get_channels();
    std::list<int> fds;
    fds.push_back(usr.get_fd());
    for(std::vector<std::string>::iterator it = chans.begin(); it != chans.end(); it++) {
        Channel chan = srv.get_channel_by_name(*it);
        std::list<User> users = chan.get_users();
        for(std::list<User>::iterator ite = users.begin(); ite != users.end(); ite++) {
            fds.push_back(ite->get_fd());
        }
    }
    fds.sort();
    fds.unique();
    std::list<int>::iterator it = fds.begin();
    while (it != fds.end()) {
        send_update(usr, command, params, *it);
        it++;
    }
}

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

bool check_user_name(std::string str) {
    if (str.find('@') != std::string::npos || str.find(' ') != std::string::npos)
        return false;
    return true;
}

bool check_nick_availibility(std::string str, Server & srv) {
    std::map<int, User> & users = srv.get_users();
    std::map<int, User>::iterator it = users.begin();
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

std::string prefix(int num) {
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

std::string allupper(std::string str)
{
	for(size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return(str);
}

std::map<int, std::string> get_msgs(void) {
    std::map<int, std::string> msgs;
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
