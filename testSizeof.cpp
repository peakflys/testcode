#include <iostream>

void func(char param[10])
{
    printf("%d\n", sizeof(param));
}

void func1(char (&param)[10])
{
    printf("%d\n", sizeof(param));
}

int main()
{
    char array[] = "abcdefghi";
    printf("%d\n", sizeof(array));
    char* p = "abcdefghi";
    printf("%d\n", sizeof(p));
    func(array);
    func1(array);
    printf("%d\n", sizeof(char[2]));
    printf("%d\n", sizeof(char&));
    return 0;
}
