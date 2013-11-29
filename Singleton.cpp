/**
 *\brief 
 */
#include <iostream>
#include "Singleton.h"
using namespace std;
class Test : public Singleton<Test>
{
	public:
		Test() : a(10),b(100),name("tzl")
		{
		}
		int a;
		int b;
		string name;
};
int main()
{
	cout<<Test::getMe().a<<" "<<Test::getMe().b<<" "<<Test::getMe().name<<endl;
	return 0;
}
