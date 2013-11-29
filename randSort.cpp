#include <iostream>

using namespace std;

__thread unsigned int seedp = 0;

static int randBetween(int min,int max)
{
	if(min == max)
		return min;
	else if(min < max)
		return min + (int)(((double)max - (double)min + 1.0) * rand_r(&seedp) / (RAND_MAX + 1.0));
	else
		return max + (int)(((double)min - (double)max + 1.0) * rand_r(&seedp) / (RAND_MAX + 1.0));
}

//这种方法有缺陷，当传进去的是一个变量时，结果会清零
// void Swap(int& nOne, int& nTwo)
// {
// 	nOne = nOne + nTwo;
// 	nTwo = nOne - nTwo;
// 	nOne = nOne - nTwo;
// }
void Swap(int& nOne, int& nTwo)
{
    int nTemp;
    nTemp = nOne;
    nOne = nTwo;
    nTwo = nTemp;
}
/*
//返回一个在区间[nBeg, nEnd]内的随机数
int Random(int nBeg, int nEnd)
{
    assert(nEnd >= nBeg);
    if (nBeg == nEnd)
    {
        return nBeg;
    }
    else
    {
        return rand() % (nEnd - nBeg + 1) + nBeg;
    }
}*/
void RandomizeInPlace(int* pnA, int nLen)
{
    static bool s_bFirst = false;
    if (!s_bFirst)
    {
        //srand(time(NULL));
		seedp = time(0);
        s_bFirst = true;
    }
    
    for (int i = 0; i < nLen; ++i)
    {
       // Swap(pnA[i], pnA[Random(i, nLen - 1)]);
        Swap(pnA[i], pnA[randBetween(i, nLen - 1)]);
    }
}
int main()
{
    int nArray[20];
    int i, j;
    for (i = 1; i <= 20; ++i)
    {
        int nCnt = i;
        while (nCnt--)
        {
            for (j = 0; j < i; ++j)
            {
                nArray[j] = j;
            }
            RandomizeInPlace(nArray, i);
            for (j = 0; j < i; ++j)
            {
                printf("%d ", nArray[j]);
            }
            printf("\n");
        }
        printf("\n");
    }
    return 0;
}
