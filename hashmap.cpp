/**
 *\author peakflys
 *\brief 演示hash_map键值更改造成的问题
 */
#include <iostream>
#include <ext/hash_map>
struct Unit
{
	char name[32];
	unsigned int score;
	Unit(const char *_name,const unsigned int _score) : score(_score)
	{
		strncpy(name,_name,32);
	}
};
int main()
{
	typedef __gnu_cxx::hash_map<char*,Unit*> uHMap;
	typedef uHMap::value_type hmType;
	typedef uHMap::iterator hmIter;
	uHMap hMap;
	Unit *unit1 = new Unit("peak",100);
	Unit *unit2 = new Unit("Joey",20);
	Unit *unit3 = new Unit("Rachel",40);
	Unit *unit4 = new Unit("Monica",90);
	hMap[unit1->name] = unit1;
	hMap[unit2->name] = unit2;
	hMap.insert(hmType(unit3->name,unit3));
	hMap.insert(hmType(unit4->name,unit4));
	for(hmIter it=hMap.begin();it!=hMap.end();++it)
	{
		std::cout<<it->first<<"\t"<<it->second->score<<std::endl;//正常操作
	}
	hmIter it = hMap.begin();
	strncpy(it->first,"cc",32);//强行更改
	for(hmIter it=hMap.begin();it!=hMap.end();++it)
	{
		std::cout<<it->first<<"\t"<<it->second->score<<std::endl;//死循环，原因参加上面++操作说明
	}
	for(hmIter it=hMap.begin();it!=hMap.end();++it)
	{
		Unit *unit = it->second;
		hMap.erase(it++);
		delete unit; //因为死循环，造成多次delete多次而宕机
	}
	return 0;
}
