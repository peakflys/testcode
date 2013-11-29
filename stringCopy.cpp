/**
 *\brief string Copy-On-Write 特性
 */
#include <iostream>
using namespace std;
int main()
{
	string s1("tzl");
	string s(s1);
	cout<<(void *)(s1.c_str())<<"/"<<(void *)s.c_str()<<endl;
	s += "&nqz";
	cout<<(void *)(s1.c_str())<<"/"<<(void *)s.c_str()<<endl;
	return 0;
}
