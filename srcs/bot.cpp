#ifndef BOT_CPP
# define BOT_CPP

#include "../include/server.hpp"


void	bot(vector<string> *vec, User & usr, Server & srv)
{
	(void)srv;
	(void)usr;
	(void)vec;
	srand(time(NULL));
	int face = atoi(vec->front().c_str());
	

}

#endif