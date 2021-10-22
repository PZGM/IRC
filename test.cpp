#include "include/server.hpp"

// void yo(string s)
// {
//     std::cout << "yo = " << s << std::endl;
// }
// void mdr(string s)
// {
//     std::cout << "mdr = " << s << std::endl;
// }





// int main()
// {
//     using pfunc = void(*)(string);
//     map<string, pfunc> fmap;
//     fmap["yo"] = yo;
//     fmap["mdr"] = mdr;

//     pfunc f = fmap["yo"];
//     (*f)("fuck");
//     f = fmap["mdr"];
//     (*f)("fuck");

// }




int main()
{
    std::cout << "ca marche" << std::endl;
    write(4, "mdr", 3);
}