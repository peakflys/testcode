#include <iostream>
#include <vector>
//#include <algorithm>

struct Data
{
	Data()
	{
		bzero(this,sizeof(*this));
	}
	Data(int _a=0,int _b=0):a(_a),b(_b){}
	bool operator==(Data &data)
	{
		return this->a == data.a;
	}
	int a,b;
};
template<typename T>
class Function
{
	public:
		Function(T _t) : t(_t){}
		bool operator()(T &temp)
		{
			return t==temp;
		}
	private:
		T t;
};
class A
{
	public:
		A()
		{
			DV.clear();
		}
		void add(Data data)
		{
			DV.push_back(data);
		}
		bool equal(int value)
		{
			return value == 3;
		}
		typedef std::vector<Data>::iterator DVIT;
		DVIT myfind(int value)	
		{
			Data data(value);
			Function<Data> f(data);
			return std::find_if(DV.begin(),DV.end(),f);
		}
	private:
		std::vector<Data> DV;
};

int main()
{
	A aa;
	for(int i=0;i<10;i++)
	{
		Data data(i,i*i);
		aa.add(data);	
	}
	A::DVIT it = aa.myfind(7);
	std::cout<<it->a<<" "<<it->b<<std::endl;
	return 0;
}
