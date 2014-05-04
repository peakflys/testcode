#include <iostream>

using namespace std;

class Test
{
    public:
        Test(){cout<<"constructor is here!"<<endl;}
        ~Test(){cout<<"destructor is here!"<<endl;}
};

int main()
{
    Test t;
    while(1)
    {
        //do nothing
    }
    return 0;
}
