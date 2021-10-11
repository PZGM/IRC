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

int FuncA()
{
    return 1;
}

int FuncB()
{
    return 2;
}


int main()
{
    // Int map
    map<string,int(*)()> int_map;
    int_map["A"] = FuncA;
    // Call it
    cout<<int_map["A"]()<<endl;

    // Add it to your map
    map<string, int(*)()> any_map;
    any_map["A"] = FuncA;
    any_map["B"] = FuncB;

    // Call
    cout<<reinterpret_cast<int(*)()>(any_map["B"])()<<endl;
}