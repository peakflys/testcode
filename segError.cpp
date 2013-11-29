/**
 *\author peakflys 
 *\brief 堆栈崩溃问题
 */
#include <iostream>
#include <fstream>
using namespace std;

const unsigned int DATA_BUFFER = 64 * 1024;

class Test
{
public:
	Test(const string _name) : name(_name)
	{
	}
	void test();
private:
	string name;
};

void Test::test()
{
	ofstream out(name.c_str(),ios_base::binary);	
	if(!out)
		return;
	cout<<name<<endl;
	int data[DATA_BUFFER * 1024];
	bzero(data,sizeof(data));
}

int main()
{
	Test t("test");
	t.test();
	return 0;
}
