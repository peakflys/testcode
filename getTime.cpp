#include <iostream>
#include <time.h>
using namespace std;
int main()
{
	struct tm current,tmX;
	time_t now = time(0),timeX = 1;
//	current = *gmtime(&now);
	current = *localtime(&now);
	cout<<"现在的时间："<<asctime(&current)<<endl;
	while(timeX != 0)
	{
		cout<<"请输入需要查询的时间点: ";
		cin>>timeX;
		if(timeX)
		{
		//	tmX = *gmtime(&timeX);	
			tmX = *localtime(&timeX);	
			cout<<"查询的时间是："<<asctime(&tmX)<<endl;
		}
	}
	return true;
}
