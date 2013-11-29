/**
 *\brief CPU对内存对齐的优化原则是：保证每个数据的偏移地址都能整除数据的大小，最后结果保证是对齐长度的整数倍！
 */
#include <iostream>
using namespace std;

//变量在结构题中的偏移
#define OFFSET_OF_STRUCT(type, var) ((size_t)(&((type *)NULL)->var))

struct Test
{
	short a;
	short b;
	short c;
};

struct TestA
{
	int aa;
	char a;
	short b;
	char c; 
}__attribute__((packed));
#pragma pack(4)
struct TestB
{
	int aa; //第一个成员，放在[0,3]偏移的位置，
	char a; //第二个成员，自身长为1，#pragma pack(4),取小值，也就是1，所以这个成员按一字节对齐，放在偏移[4]的位置。
	short b; //第三个成员，自身长2，#pragma pack(4)，取2，按2字节对齐，所以放在偏移[6,7]的位置。
	char c; //第四个，自身长为1，放在[8]的位置。
};
struct TestC
{
	int a;
	bool b;
	short f;
	short cr:5;
	short cg:6;
	short cb:3;
	short st;
	float s;
};
#pragma pack()
int main()
{
//	cout<<sizeof(Test)<<"/"<<sizeof(TestA)<<"/"<<sizeof(TestB)<<endl;
	cout<<OFFSET_OF_STRUCT(TestC,f)<<"   "<<OFFSET_OF_STRUCT(TestC,st)<<" "<<OFFSET_OF_STRUCT(TestC,s)<<endl;
}
