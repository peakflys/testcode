/**
 *\brief 打�N!后�有度少0
 */
#include <iostream>
using namespace std;

unsigned long getNmul(unsigned int nN)//很容易溢出
{
	if(1 == nN || 0 == nN)
		return 1;
	else
		return (unsigned long)nN*getNmul(nN-1);
}

int getAns(int nN)
{
    int nAns = 0;
    while (nN)
    {
        nAns += nN / 5;
        nN /= 5;
    }
    return nAns;
}

int main()
{
    while (1)
    {
        int nN;
        scanf("%d", &nN);
		if(-1 == nN)
			break;
        printf("multiN:%lu,0 nums :%d\n", getNmul(nN),getAns(nN));
    }
    
    return 0;
}
