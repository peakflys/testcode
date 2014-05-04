#include <iostream>

union U
{
    short a;
    char b[2];
};

int main()
{
    U u;
    u.a = 0x0102;
    if(u.b[0] == 0x01)
        std::cout<<"big endian"<<std::endl;
    else if(u.b[0] == 0x02)
        std::cout<<"little endian"<<std::endl;
    return 0;
}
