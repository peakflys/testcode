/**
 */
#include <iostream>
using namespace std;
class Base
{
	public:
	/*	void print()
		{cout<<"This is print()"<<endl;}*/
		virtual void vprint1()
		{cout<<"This is vprint1()"<<endl;}
		virtual void vprint2()
		{cout<<"This is vprint2()"<<endl;}
};
int main()
{
	typedef void(*pFun)(void) ;
	pFun pf = NULL;
	int *vt = NULL;
	Base b;
	int size =  sizeof(&Base::vprint1);
	cout<<"Base VirtualTable addr : "<<(int *)&b<<endl;
	vt = (int *)*(int *)&b;
	cout<<"Base First VirtualFunc addr: "<<vt[0]<<endl;
	//pf = (void *)*(int *)&b;//error
	pf = (pFun)vt[0];
	pf();
	cout<<"Base Second VirtualFunc addr: "<<vt[1]<<endl;
	pf = (pFun)(vt[4]);
	pf();
	return 0;
}
