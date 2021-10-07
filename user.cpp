#ifndef USER_CPP
# define USER_CPP

# include "server.hpp"

// bool verif(string str)
// {
// 	if (s)
// }

void user(vector<string> *vec, User & usr) {
	std::cout << "Je suis dans user" << std::endl;
	if (vec->size() < 4)
		std::cout << "wrong format" << std::endl;
	else {
		vector<string>::iterator it = vec->begin();
		// std::cout << *it << std::endl;
		if ((*it++).size() <= 63 && ((*it)[0] == '1' || (*it)[0] == '0') && (*it++).size() == 1)
		{
			it = vec->begin();
			usr.set_user(*it++);
			usr.set_flags(*it++);
			it++;
			string tmp;
			while (it != vec->end())
			{
				tmp.insert(tmp.length(), (*it));
				if ((++it)!= vec->end())
				tmp.insert(tmp.length(), " ");
			}
			std::cout << "tmp  = |"<< tmp << "|"<< std::endl;
			if (usr.set_real(*it))
				cout<<"real good"<<endl;
		}

		// cout<<"user good"<<endl;
		// std::cout << *it << std::endl;
		// if ((*it)[0])
		// 	cout<<"flag good"<<endl;
		// std::cout << *it << std::endl;
		// it++;
		// std::cout << *it << std::endl;
	}

}

#endif