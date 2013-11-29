#include <iostream>
using namespace std;

char * compress1(const char *src)
{
	string ret;
	const int len = strlen(src);
	if(0 == len)
		return "";
	int pos = 0, count = 0;
	bool repeat = false;
	char temp = src[pos];
	ret += temp;
	while(++pos < len)
	{
		if(!repeat)	
		{
			if(src[pos] == temp)
			{
				repeat = true;
				++count;
				continue;
			}
			else
			{
				ret += src[pos];
				temp = src[pos];
				continue;
			}
		}
		else
		{
			if(src[pos] == temp)
			{
				++count;
				continue;
			}
			else
			{
				ret += count;
				ret += temp;
				temp = src[pos];
				repeat = false;
				count = 0;
				continue;
			}
		}
	}
	return const_cast<char *> (ret.c_str());
}

int main()
{
	char a[] = "aaabbbbbbcddddcca";
	cout<<"before:\t"<<a<<"  :"<<strlen(a)<<endl;
	string t = compress(a);
	cout<<"after :\t"<<t<<"  :"<<strlen(t.c_str())<<endl;
	return 0;
}
