#include <iostream>
#include <vector>
//#include <algorithm>
//std::sort和std::greater的用法
using namespace std;

int main()
{
	int a[] = {10,5,20,55,11};
	vector<int> vi(a,a+5);
	for(int i=0;i<vi.size();++i)
		cout<<vi[i]<<endl;
	cout<<endl;
	sort(vi.begin(),vi.end(),greater<int>() );
	for(int i=0;i<vi.size();++i)
		cout<<vi[i]<<endl;
	return 0;
}
