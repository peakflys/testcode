#include <iostream>

using namespace std;

#define check_func(func) \
    do {\
        if(1 != (ret = func))\
        {\
            result_id = ret;\
            goto loop;\
        }\
    }while(0)

int test(int a, int b)
{
    if(a < b)
        return 1;
    else if(a == b)
        return 0;
    else
        return -1;
}

int main()
{
    char arr[][10] = {"China","American"};
    char *p = arr[0];
    printf("%s\n", p);
    printf("%s\n", p+10);
    return 0;
    int a, b, ret, result_id;
    cin >> a >> b;
    check_func(test(a,b));
    cout<<"this is next"<<endl;
    return 0;
loop:
    cout<<"this is loop"<<endl;
    return 0;
}
