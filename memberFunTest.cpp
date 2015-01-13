/**
 *\author peakflys 
 *\brief C方式实现的C++回调
 */
#include <iostream>
#include <vector>

#define COUNTARRAY(a) sizeof(a)/sizeof(a[0])

class User
{
	public:
		User(std::string _name,bool _online) : name(_name),online(_online)
		{
		}
		const std::string& getName() const
		{
			return this->name;
		}
		bool checkOnLine()
		{
			return online;
		}
	private:
		std::string name;
		bool online;
};

class Test;
typedef void(Test::*pFun)(const User&);//成员函数

class Test
{
	public:
		Test(const std::vector<User>& _userList) : userList(_userList)
		{
		}

		void print(const User& user);

		void execEvery(pFun fun);

	private:
		std::vector<User> userList;
};

void Test::print(const User& user)
{
	std::cout<<user.getName()<<" ";
}

void Test::execEvery(pFun fun)
{
	for(std::vector<User>::iterator it=userList.begin();it!=userList.end();++it)
	{
		if((*it).checkOnLine())
			(this->*fun)(*it); //注意格式
	}
	std::cout<<std::endl;
}

int main()
{
	User um[] = {User("张三",true),User("李四",false),User("王二",true),User("麻子",true)};
	std::vector<User> vu(um,um+COUNTARRAY(um));	
	Test t(vu);
	t.execEvery(&Test::print);
	return 0;
}
