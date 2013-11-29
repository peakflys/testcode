#include <iostream>
class Test
{
	public:
		static const short a = 10;
		static const float f = 10.12f;
		static const char c = 10;
		static const std::string s =  "";
};

int main()
{
	Test t;
	std::cout<<t.a<<" "<<t.f<<int(t.c)<<std::endl;	
	return 0;
}
