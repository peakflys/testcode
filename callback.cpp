/**
 *\author peakflys 
 *\brief C++方式实现的C++回调
 */
#include <iostream>
#include <vector>
#include <tr1/functional>

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

class Test
{
	public:
		Test(const std::vector<User>& _userList) : userList(_userList)
		{
		}

		void static print(const User& user);

		void execEvery(std::tr1::function<void (const User&)> func);
	private:
		std::vector<User> userList;
};

void Test::print(const User& user)
{
	std::cout<<user.getName()<<" ";
}

void Test::execEvery(std::tr1::function<void (const User&)> func)
{
	for(std::vector<User>::iterator it=userList.begin();it!=userList.end();++it)
	{
		if((*it).checkOnLine())
			func(*it); //注意格式
	}
	std::cout<<std::endl;
}

int main()
{
	User um[] = {User("张三",true),User("李四",false),User("王二",true),User("麻子",true)};
	std::vector<User> vu(um,um+COUNTARRAY(um));	
	Test t(vu);
	t.execEvery(std::tr1::bind(Test::print,std::tr1::placeholders::_1));
	return 0;
}
