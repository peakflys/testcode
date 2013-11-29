#include "checkTime.h"
#include <fstream>
const unsigned int MAXNUM = 100000;
int main()
{
	FUNCTIME("RU"_S(__LINE__));	
	std::ofstream outFile;
	outFile.open("ranTest.log");
	srand(time(0));
	for(int i=0;i<MAXNUM;++i)	
	{
		outFile<<rand()%1000<<"\t";
		if(i && 0 == i%5)
			outFile<<"\n";
	}
	outFile.close();
	return 0;
}

