#include "server.hpp"

string allupper(string str)
{
	for(size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	if (str[str.length() -1] == '\n')
		str.resize(str.length() - 1);
	return(str);
}