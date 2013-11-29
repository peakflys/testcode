#include <iostream>
using namespace std;
/**
 *\brief 拷贝函数实现
 */
const char* strcopy(char*des,const char *src)
{
	char *ret = des;
	if(des && src)
	{
		while(*(des++) = *(src++))
			;
	}
	return ret;
}
/**
 *\brief 字符一次循环移动，默认为右移
 */
void swapChar(char *src,bool right=true)
{
	if(src && strlen(src))
	{
		int len = strlen(src);
		if(right)
		{
			char temp = src[len-1];
			for(int i=len-1;i>0;--i)
				src[i] = src[i-1];
			src[0] = temp;
		}
		else
		{
			char temp = *src;
			for(int i=1;i<len;++i)
				src[i-1] = src[i];
			src[len-1] = temp;
		}
	}
}
/**
 *\brief 字符串循环移动
 */
void loopRMove(char *src,int step)
{
	if(src && step>0)
	{
		int len = strlen(src);
		int loop = step%len;
		if(0 == len || 0 == loop)
			return;
		while(loop--)
			swapChar(src);		
	}
}
int main()
{
	string str1 = "hello world";
	string str2 = str1;

	printf ("Sharing the memory:\n");
	printf ("\tstr1's address: %x\n", str1.c_str() );
	cout<<str1.c_str()<<endl;
	printf ("\tstr2's address: %x\n", str2.c_str() );
	cout<<str2.c_str()<<endl;

	str1[1]='q';
	str2[1]='w';

	printf ("\fter Copy-On-Write:\n");
	printf ("\tstr1's address: %x\n", str1.c_str() );
	cout<<str1.c_str()<<endl;
	printf ("\tstr2's address: %x\n", str2.c_str() );
	cout<<str2.c_str()<<endl;
	return 0;
}
