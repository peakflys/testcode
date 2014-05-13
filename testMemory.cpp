/**
 *\brief test memory usage
 *\cat /proc/$(pgrep memory|tail -1)/status|grep VmSize|awk '{print $2}'
 *\cat /proc/$(pgrep memory|tail -1)/status|grep VmRSS|awk '{print $2}'
 */
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

void testStack(unsigned int allNum, unsigned int valueNum) 
{
    int t[allNum];
    for(int i=0;i<valueNum;++i)
        t[i] = i;
    printf("in function stack test\n");
    getchar();
}

int* testHeap(unsigned int allNum, unsigned int valueNum) 
{
    int* pt = new int[allNum];
    for(int i=0;i<valueNum;++i)
        pt[i] = i;
    printf("in function heap test\n");
    getchar();
    return pt;
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("usage: ./memory 100 10");
        return 0;
    }
    testStack(atoi(argv[1]),atoi(argv[2]));
    printf("finish function stack test\n");
    int* pt = testHeap(atoi(argv[1]),atoi(argv[2]));
    printf("finish function heap test\n");
    getchar();
    int* pt1 = testHeap(atoi(argv[1]),atoi(argv[2]));
    printf("finish function heap test\n");
    getchar();
    delete [] pt;
    printf("delete pt heap memory\n");
    getchar();
    delete [] pt1;
    printf("delete pt1 heap memory\n");
    getchar();
    return 0;
}
