#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

const int rand5()
{
    return rand() % 5 + 1;
}

int rand7base5()
{
   int a = 5 * (rand5() - 1) + rand5(); //rand 1-25
   if(a > 21) return rand7base5();
   return a % 7 + 1;
}

int main()
{
    srand(time(0));
    int rt[7];
    memset(rt, 0, sizeof(rt));
    const static int countMax = 10000000;
    for(int i = 0; i < countMax; ++i)
    {
        rt[rand7base5()-1] ++;
    }
    for(int i = 0; i < 7; ++i) cout << i+1 << ": " << rt[i] << " " << (static_cast<double> (rt[i]))/countMax << endl;
    return 0;
}
