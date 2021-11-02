#include "../include/server.hpp"

string allupper(string str)
{
	for(size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return(str);
}

bool	close_connection(int i, pollfd &fds, map<int, User> & users, Server & srv)
{
	bool close_conn = false;
	char buff[BUFF] = {0};
	string input = "";
	do {
		memset(buff, 0, sizeof(buff)); 
		int rc = recv((&fds)[i].fd, buff, sizeof(buff),  MSG_DONTWAIT); //receive data
		if (rc < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				std::cerr << " recv error" << std::endl;
				close_conn = true;
			}
			return false;
		}
		if (rc == 0)
		{
			std::cout << "connection close" <<std::endl;
			users.erase(users.find((&fds)[i].fd));
			std::cout << "user deleted from database" << std::endl;
			close_conn = true;
			break;
		}
		input += buff;
		if (input.find("\n")) {
			vector<string> * vec = split(input, "\n");
			vector<string>::iterator it = vec->begin();
			while (it != vec->end()){
				parsing(*it, users[(&fds)[i].fd], srv);
				it++;
			}
			input = "";
		}
	} while(true);
	if (close_conn)
	{
		std::cout << "je sors ici =" << (&fds)[i].fd << std::endl;
		close((&fds)[i].fd);
		(&fds)[i].fd = -1;
		return true;
	}
	return false;
}

