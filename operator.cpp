#include <iostream>
#include <vector>
class Test
{
	public:
		Test(const int _grade,const char *_name,const short _score) : grade(_grade),score(_score)
		{
			strncpy(name,_name,32);
		}
		//函数后面也要加上const，因为std::vector的operator==()传入的都是const参数
		bool operator==(const Test& other) const
		{
			return grade==other.grade;
		}
	//	friend bool operator == (const Test& me,const Test& other);
	private:
		int grade;
		char name[32];
		short score;
};
/*
bool operator==(const Test& me,const Test& other)
{
	return me.grade==other.grade;
}*/
using namespace std;
int main()
{
	vector<Test> vt1,vt2;
	Test t1(5,"youjie",100);
	Test t2(3,"xxx",80);
	vt1.push_back(t1);
	vt2.push_back(t2);
	if(vt1 == vt2)
	{
		cout<<"vt1==vt2"<<endl;
	}
	else
		cout<<"vt1!=vt2"<<endl;
	return 0;
}
