#include "../include/server.hpp"

void	who(vector<string> *vec, User & usr, Server & srv)
{
    bool op = false;
	if (vec->size() > 2 || (vec->size() == 2 && vec->back() != "o"))
    {
        std::cerr << "error args who" << std::endl;
        send_error(461,usr); //random value in send error need to find the good one
        return;
    }
    if (vec->back() == "o") { //search just for operator
        op = true;
        vec->pop_back();
    }
    vector<string> uchan;
    vector<string>::iterator uit;
    Channel chan;
    list<User> lst;
    list<User>::iterator it;

    if (vec->size() == 0 || (vec->size() == 1  && vec->front() == "0"))
	{
		uchan = usr.get_channels();
        uit = uchan.begin();
        
        for (uit; uit != uchan.end(); uit++) {
            chan = srv.get_channel_by_name(*uit);
            lst = chan.get_users();
            for(it = lst.begin(); it != lst.end(); it++){
                if (op == true && (*it).is_oper() == false)
                    continue;
                //send le machin
            }
        }
		return;
	}
    else 
    {
        uchan = usr.get_channels();
        uit = uchan.begin();
        for (uit; uit != uchan.end(); uit++) {
            chan = srv.get_channel_by_name(*uit);
            lst = chan.get_users();
            for(it = lst.begin(); it != lst.end(); it++){
                if (op == true && (*it).is_oper() == false)
                    continue;
                if (((*it).get_nick() == vec->back()) || ((*it).find_channel(vec->back()))) {
                //send le machin
                }
            }

        }
		return;
}