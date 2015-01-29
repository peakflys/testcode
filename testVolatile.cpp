#include <iostream>
using namespace std;

int something = 0;
volatile int flag = false;

void test()
{
    something = 0;
    //在加上-O2的优化下，something的赋值不管flag是否为volatile都会放在后面
    //此例仅作论证通过volatile flag的方式无法保证多线程下上下文变量的值
    flag = true;       
    something = 15;
}

int main()
{
    test();
    return 0;
}
