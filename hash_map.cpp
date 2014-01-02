#include <ext/hash_map>
#include <ext/hash_fun.h>
#include <iostream>

using namespace std;

struct str_hash
{
    size_t operator()(const string& str) const
    {
        return __gnu_cxx::__stl_hash_string(str.c_str());
    }
};

//no mark string compare param
typedef __gnu_cxx::hash_map<string,int,str_hash> hashMap;

int main()
{
    hashMap hm;
    for(int i=0;i<100;++i)
    {
        string s("test");
        char temp[8];
        sprintf(temp,"%d",i);
        s += string(temp); 
        hm[s] = i;
    }
    string bingo;
    while(string("quit") != bingo)
    {
        cin>>bingo;
        hashMap::iterator it = hm.find(bingo);
        if(it != hm.end())
            cout<<it->second<<endl;
        else
            cout<<"not found"<<endl;
    }
    return 0;
}
