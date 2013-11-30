#include <iostream>

using namespace std;

class Base
{
public:
	//param is not dynamic
	virtual void print(const int a = 10) {cout<<a<<endl;}
};

class Derive : public Base
{
public:
	virtual void print(const int a = 100) {cout<<a<<endl;}
};

int main()
{
	Base *pb = new Derive;
	pb->print();
	return 0;
}

