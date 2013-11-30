#include <iostream>

using namespace std;

class Test
{
public:
	Test(const int a=100) : a(a){}
	//gcc 4.1.2 will omit inline, but if -O1 and above, function
	//is inline, even not declare inline.
	inline const int getData() const {return a;}
private:
	int a;
};

int main()
{
	Test t;
	int a = t.getData();
	cout<<a<<endl;
	return 0;
}
