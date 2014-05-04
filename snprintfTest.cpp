#include <iostream>

using namespace std;

int main()
{
    const string s1("tian");
    const string s2("niu");
    char buf1[5]; 
    //snprintf会为buf拼接上结束符的！
    //snprintf写入(加上末尾补充的\0)不大于指定长度的数据
    int ret1 = snprintf(buf1,sizeof(buf1),"%s%s",s1.c_str(),s2.c_str());
    cout<<buf1<<"\t"<<ret1<<endl;
    if(ret1 >= sizeof(buf1))
        cout<<"memory buffer1 is not enough!"<<endl;
    char buf2[s1.size()+s2.size()+1]; //C99 support
    int ret2 = snprintf(buf2,sizeof(buf2),"%s%s",s1.c_str(),s2.c_str());
    cout<<buf2<<"\t"<<ret2<<endl;
    if(ret2 >= sizeof(buf2))
        cout<<"memory buffer2 is not enough!"<<endl;
    return 0;
}
