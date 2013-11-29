#include <iostream>

#define OFFSET_STRUCT(T,a) (size_t)&(((T*)0)->a)

struct Test
{
	int a;
	double b;
	char c;
	long d;
};

int main()
{
	/**
	 * note: get nullptr member is invalid, but get the address is valid!
	 */
	Test *t = 0;
	std::cout<<(void *)t<<std::endl; //ok
	//std::cout<<(*t).a<<std::endl;//wrong
	std::cout<<OFFSET_STRUCT(Test,d)<<std::endl; //ok
	std::cout<<(size_t)&(t->c)<<std::endl; //ok
	return 0;
}
