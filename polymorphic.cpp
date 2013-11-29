#include <iostream>

class ACBASE
{
public:
	virtual ~ACBASE() = 0;
};

ACBASE::~ACBASE() {}

class BASE : protected ACBASE
{
public:
	BASE(int a)
	{
	}
	~BASE()
	{
	}
	virtual void test()=0;
};

class DERIVE : public BASE
{
public:
	DERIVE(int b) : BASE(10)
	{
	}
	~DERIVE()
	{
	}
	void test()
	{
		std::cout<<__FILE__<<" "<<__PRETTY_FUNCTION__<<std::endl;
	}
};

class DERIVE1 : public BASE
{
public:
	DERIVE1(int b) : BASE(10)
	{
	}
	~DERIVE1()
	{
	}
	void test()
	{
		std::cout<<__FILE__<<" "<<__PRETTY_FUNCTION__<<std::endl;
	}
};

int main()
{
	DERIVE d(2);
	d.test();
	DERIVE1 dd(1);
	dd.test();
	return 0;
}
