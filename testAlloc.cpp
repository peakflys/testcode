#include <iostream>
#include <map>
#include <vector>
#ifdef _POOL
#include <ext/pool_allocator.h>
#endif

const static unsigned int Count = 1000000;

using namespace std;

struct Data
{
    int a;
    double b;
};

int main()
{
#ifdef _POOL
    map<int, Data, less<int>, __gnu_cxx::__pool_alloc<pair<int, Data> > > mi;
    vector<Data, __gnu_cxx::__pool_alloc<Data> > vi;
#else
    map<int, Data> mi;
    vector<Data> vi;
#endif

    for(int i = 0; i < Count; ++i)
    {
        Data d;
        d.a = i;
        d.b = i * i;
        mi[i] = d;
        vi.push_back(d);
    }
    mi.clear();
#ifdef _POOL
    vector<Data, __gnu_cxx::__pool_alloc<Data> >().swap(vi);
#else
    vector<Data>().swap(vi);
#endif
    for(int i = 0; i < Count; ++i)
    {
        Data d;
        d.a = i;
        d.b = i * i;
        mi[i] = d;
        vi.push_back(d);
    }
    return 0;
}
