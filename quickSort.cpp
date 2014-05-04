#include <iostream>
#include <iterator>
#include <algorithm>
#include <cassert>

using namespace std;

template <typename T>
void quickSort(T* pIndex, const int num)
{
    assert(pIndex);
    if(num <= 1)
        return;
    int i = 0, j = num -1, guard = pIndex[0];
    while(i < j)
    {
        for(; j>i; --j) 
            if(pIndex[j] < guard)
            {
                pIndex[i] = pIndex[j];
                break;
            }
        for(; i<j; ++i)
            if(pIndex[i] > guard)
            {
                pIndex[j] = pIndex[i];
                break;
            }
    }
    pIndex[i] = guard;
    quickSort(pIndex,i);
    quickSort(&pIndex[i+1],num-i-1);
}

template <typename T>
void quickSort(T* pIndex, const int begin, const int end)
{
    if(begin >= end)
        return;
    T guard = pIndex[end];
    int middle = begin;
    for(int i=begin; i<end; ++i)
    {
        if(pIndex[i] < guard)
        {
           if(i != middle) 
               swap(pIndex[middle],pIndex[i]);
           ++middle; //比guard大的第一个数的索引位置
        }
    }
    swap(pIndex[end],pIndex[middle]);
    quickSort(pIndex,begin,middle-1);
    quickSort(pIndex,middle+1,end);
}

int main()
{
    int num = 0, temp = 0;
    int array[10], backup[10];
    while(cin >> temp)
    {
        array[num] = backup[num] = temp;
        if(++num >= 10)  
            break;
    } 
    cout<<endl;
    copy(array,array+num,ostream_iterator<int>(cout,"\t"));
    cout<<endl;
    quickSort(array,num);
    copy(array,array+num,ostream_iterator<int>(cout,"\t"));
    cout<<endl;
    quickSort(backup,0,num-1);
    copy(backup,backup+num,ostream_iterator<int>(cout,"\t"));
    cout<<endl;
    return 0;
}
