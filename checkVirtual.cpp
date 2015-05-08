#include <iostream>
using namespace std;

template <typename T>
struct checkVirtual : T
{
    virtual void dummy() = 0;
    static const bool value = (sizeof(T) == sizeof(checkVirtual<T>));
};

class T1 {void dummy(){}};
class T2 {virtual void dummy(){}};

int main()
{
   cout<<checkVirtual<T1>::value<<"\t"<<checkVirtual<T2>::value<<endl; 
   return 0;
}
