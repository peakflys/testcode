#include <iostream>
using namespace std;

struct Nil;

//type identify!
//main template
template <typename T>
struct IsPointer
{
    enum { Result = false };
    typedef Nil ValueType;
};

//specialist
template <typename T>
struct IsPointer<T*>
{
    enum { Result = true };
    typedef T ValueType;
};

int main()
{
    cout<<IsPointer<int*>::Result<<endl;  //1
    cout<<IsPointer<const int*>::Result<<endl; //1
    cout<<IsPointer<int&>::Result<<endl; //0
    cout<<IsPointer<int>::Result<<endl; //0
    IsPointer<int*>::ValueType i = 1;
//    IsPointer<int>::ValueType j = 1; //not define
    cout<<i/*<<"\t"<<j*/<<endl;
    return 0;
}
