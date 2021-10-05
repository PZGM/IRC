#include "server.hpp"

string allupper(string str)
{
	for(size_t i = 0; i < str.length(); i++)
		str[i] = toupper(str[i]);
	return(str);
}