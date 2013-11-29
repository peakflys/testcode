/**
 *\brief 测试GCC扩展__builtin_return_address的使用
 *\brief 需要使用objdump -Cd exe > exe.asm 或者 -CSd 然后在asm文件里查找打出的地址
 */
#include <iostream>

using namespace std;
void print()
{
	//__builtin_return_address的参数0表示上层调用地址(即本层的返回地址)，1表示上上层调用地址
	cout<<__builtin_return_address(0)<<"/"<<__builtin_return_address(1)<<endl;
}
void test()
{
	print();
}
int main()
{
	test();
	return 0;
}
