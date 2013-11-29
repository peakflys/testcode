/**
 *\author peakflys 
 *\brief 堆栈崩溃问题
 */
#include <iostream>
using namespace std;

struct Temp
{
	int a;
	unsigned char b[4];
};

void fill(unsigned char *data)
{
	for(int i=0;i<20;++i)
	{
		data[i] = i;
		cout<<"data["<<i<<"]:\t"<<(void *)&data[i]<<endl;
	}
}

int main()
{
	Temp tt;
	cout<<"tt:\t"<<&tt<<endl;
	string names[] = {"a","b","c","d"};
	for(int i=0;i<4;++i)
		cout<<"names["<<i<<"]:\t"<<(void *)&names[i]<<endl;

	cout<<"before"<<endl;
	fill((unsigned char *)&tt);
	cout<<"end"<<endl;

	for(int i=0;i<4;++i)
		cout<<"names["<<i<<"]:\t"<<(void *)&names[i]<<endl;
	return 0;
}
