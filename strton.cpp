#include <iostream>
using namespace std;
int main()
{
	char s[] = "Golden Global      View,disk * desk";
	const char *d = " ,*";
	char *p;
	p = strtok(s,d);
	while(p)
	{
		printf("%s\n",p);
		p=strtok(NULL,d);
	}
	return 0;
}
