/**
 *\brief virtual function test case
 *\author peakflys
 *\date Sun Dec  1 14:32:47 CST 2013
 */
#include <iostream>

using namespace std;

class Base
{
public:
	virtual void print(const int a = 10) {cout<<"Base: "<<a<<endl;}
};

class Derive : public Base
{
public:
	virtual void print(const int a = 100) {cout<<"Derive: "<<a<<endl;}
};

int main()
{
	Base *pb = new Derive;
	pb->print();
	Base& rb = *pb;
	rb.print();
	Derive d;
	d.print();
	Base *pbb = &d;
	pbb->print();
	Base& rbb = d;
	rbb.print();
	Base b;
	b.print();
	Derive *pd = (Derive*)&b;
	pd->print();
	Derive& rd = *(Derive*)&b;
	rd.print();
	Derive& rdd = (Derive&)b;
	rdd.print();
	delete pb;
	return 0;
}

