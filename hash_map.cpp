#include <ext/hash_map>
#include <ext/hash_fun.h>
#include <iostream>

using namespace std;

/*
 *\breif __gnu_cxx::hash_map is not standard, 
 *\it will have some problem when key is string or long long int
 */
//solution 1
namespace __gnu_cxx
{
    template<> 
    struct hash<std::string>
    {
        size_t operator()( const std::string& x ) const
        {
            return hash< const char* >()( x.c_str() );
        }
    };

    template<> 
    struct hash<long long>
    {
        size_t operator()(long long x) const
        {
            return x;
        }
    };
}

//solution 2
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
