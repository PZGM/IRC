#ifndef JOIN_CPP
# define JOIN_CPP

#include "../include/server.hpp"

void	join(vector<string> *vec, User & usr, Server & srv)
{
	(void)vec;
	(void)usr;
	(void)srv;
	for(map<string, Channel>::iterator it = srv.get_begin_channel(); it != srv.get_end_channel(); it++)
	{
		// if (name.compare((*it).first) == 0)
		// {
		// 	std::cout << "Il faut join" << std::endl;
		// }
	}
}




#endif