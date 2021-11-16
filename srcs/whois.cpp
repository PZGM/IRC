#include "../include/server.hpp"

void	whois(vector<string> *vec, User & usr, Server & srv)
{
	User tom;
	if (srv.find_user(*vec->begin()))
	{
		tom = srv.get_user(*vec->begin());
		send_whois(usr, tom, srv);
		}
	else
	{
		send_error(401, usr);
		send_error(318, usr);

		return;
	}
}
