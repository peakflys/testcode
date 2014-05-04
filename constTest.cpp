#include <iostream>

struct Thing
{
    int valueA;
    const int valueB;
};
Thing t;

int main()
{
    printf("valueA: %d, valueB: %d",t.valueA,t.valueB);
}
