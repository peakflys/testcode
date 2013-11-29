#include <iostream>
using namespace std;
bool isBigEndian()
{
	union T
	{
		short a;
		char b;
	} t;
	t.a = 1;
	return t.b == 1;
}
int main()
{
	cout<<"本平台是：";
	if(isBigEndian())
		cout<<"小端"<<endl;
	else
		cout<<"大端"<<endl;
	return 0;
}
