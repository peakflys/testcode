#include <cstdio>
#include <ext/hash_map>
using namespace __gnu_cxx;
#include <utility>
#include <functional>
using namespace std;
#include <cstring>
#include <cassert>
#include <fstream>

#define MAX_USERNAME_LEN 40
#define P(format, ...) printf("%s %s %d " format "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__)

//调用INTEL CPU指令RDTSC来获得时间计数，便于得到代码段的性能指标
unsigned long long rdtsc()
{
#ifdef _MSC_VER /* msvc compiler */
    __asm _emit 0x0F
        __asm _emit 0x31
#else /* gcc compiler */
        unsigned long long temp;
    unsigned int low, high;
    __asm__ __volatile__("rdtsc" : "=a" (low), "=d" (high));
    temp = high;
    temp <<= 32;
    temp += low;
    return temp;
#endif
}

struct UserInfo
{
    char UserName[MAX_USERNAME_LEN];
    short Length;
};

#define MAX_USERS 600000
UserInfo* pUsers = NULL;
int UserCount = 0;

void make_hash(UserInfo* Users, int UserCount);
void make_char_hash(UserInfo* Users, int UserCount);

void test()
{
    //读入用户
    ifstream in;
    in.open("users.txt");
    if(!in.is_open())
    {
        P("regeneret file...");
        ofstream out;
        out.open("users.txt");
        for(int i=0;i<MAX_USERS;++i)
        {
            string name("test");
            char temp[8];
            sprintf(temp,"%d",i);
            name += temp;
            out<<name<<endl;
        }
        out.close();
        in.open("users.txt");
        if(!in.is_open())
        { 
            P("open file error");
            return;
        } 
    }
    pUsers = new UserInfo[MAX_USERS];
    char temp_username[MAX_USERNAME_LEN];
    while (!(in.getline(temp_username,MAX_USERNAME_LEN)).eof())
    {
        strncpy(pUsers[UserCount].UserName, temp_username, sizeof(pUsers[0].UserName)-1);
        pUsers[UserCount].Length = strlen(pUsers[UserCount].UserName);
        UserCount++;
    }
    in.close();
    P("user count=%d", UserCount);

    make_hash(pUsers, UserCount);
    make_char_hash(pUsers, UserCount);
    delete[] pUsers;
    pUsers = NULL;
}

int main()
{
    test();
    return 1;
}

//=============================================================================

#include <string>
using namespace std;

struct str_hash
{
    size_t operator()(const string& str) const
    {
        return __stl_hash_string(str.c_str());
    }
};

typedef hash_map<string, UserInfo*, str_hash> StringHash;
typedef StringHash::iterator StringHashIterator;

void test_string_find(StringHash& hash, UserInfo* Users, int UserCount)
{
    int i;
    StringHashIterator it;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        it = hash.find(Users[i].UserName);
        if (it == hash.end())
        {
            P("not found %s", Users[i].UserName);
        }
    }
    end = rdtsc();
    end -= start;
    P("string find\t\t= %llu", end);
}

void test_string_erase(StringHash& hash, UserInfo* Users, int UserCount)
{
    int i;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        hash.erase(Users[i].UserName);
    }
    end = rdtsc();
    end -= start;
    P("string erase\t= %llu", end);
    assert(hash.size()==0);
}

void make_hash(UserInfo* Users, int UserCount)
{
    hash_map<string, UserInfo*, str_hash> hh;
    int i;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        hh.insert(make_pair(Users[i].UserName, Users+i));
    }
    end = rdtsc();
    end -= start;
    P("string spend\t\t= %llu", end);
    test_string_find(hh, Users, UserCount);
    test_string_erase(hh, Users, UserCount);
}
//=============================================================================
namespace std
{
    template <>
        struct equal_to<const char*> : public binary_function<const char*, const char*, bool>
        {
            bool operator()(const char* str1, const char* str2) const
            {
                return 0==strcmp(str1, str2);
            }
        };
};

struct char_hash
{
    size_t operator()(const char* str) const
    {
        return __stl_hash_string(str);
    }
};

//typedef hash_map<const char*, UserInfo*, char_hash, std::equal_to<const char*> > CharHash;
typedef hash_map<const char*, UserInfo*, hash<const char*> > CharHash;
typedef CharHash::iterator CharHashIterator;

void test_char_find(CharHash& hash, UserInfo* Users, int UserCount)
{
    int i;
    CharHashIterator it;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        it = hash.find(Users[i].UserName);
        if (it == hash.end())
        {
            P("not found %s", Users[i].UserName);
        }
    }
    end = rdtsc();
    end -= start;
    P("char hash find\t\t= %llu", end);
}

void test_char_erase(CharHash& hash, UserInfo* Users, int UserCount)
{
    int i;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        hash.erase(Users[i].UserName);
    }
    end = rdtsc();
    end -= start;
    P("char erase\t\t= %llu", end);
    assert(hash.size()==0);
}

void make_char_hash(UserInfo* Users, int UserCount)
{
    //hash_map<const char*, UserInfo*, char_hash, std::equal_to<const char*> > hh;
    CharHash hh;
    int i;
    unsigned long long start, end;
    start = rdtsc();
    for (i=0; i<UserCount; i++)
    {
        hh.insert(make_pair(Users[i].UserName, Users+i));
    }
    end = rdtsc();
    end -= start;
    P("char spend\t\t= %llu", end);
    test_char_find(hh, Users, UserCount);
    test_char_erase(hh, Users, UserCount);
}
