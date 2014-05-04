#include <iostream>

class Base
{
    public:
        Base()
        {
            clear();
        }
        virtual ~Base() {}
        void clear()
        {
            memset(this,0,sizeof(*this));
        }
        virtual void func()
        {
            printf("func\n");
        }
};

class Derived : public Base
{};

int main()
{
    Base b;
    Derived d;
    Base* pb = &b;
    Base* pd = &d;
    Derived* pdd = &d;

    b.func();
    printf("1 ok\n");
    d.func();
    printf("2 ok\n");
    //pb->func();
    //printf("3 ok\n");
    pd->func();
    printf("4 ok\n");
    pdd->func();
    printf("5 ok\n");
}
