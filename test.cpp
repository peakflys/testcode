#include "checkTime.h"

const int MAXLEN = 64*1024*1024;

int main()
{
	/**
	 *result: CPU cache is not useful for GCC -O0&-O2 ,why???
	 */
	int *pi = new int[MAXLEN];
	{
		FUNCTIME("CPUCACHE-MAXLEN "_S(__LINE__));
		for(int i=0;i<MAXLEN;++i)
			pi[i] *= 3;
	}
	{
		FUNCTIME("CPUCACHE-MAXLEN/8 "_S(__LINE__));
		for(int i=0;i<MAXLEN;i+=8)
			pi[i] *= 3;
	}
	{
		FUNCTIME("CPUCACHE-MAXLEN/16 "_S(__LINE__));
		for(int i=0;i<MAXLEN;i+=16)
			pi[i] *= 3;
	}
	{
		FUNCTIME("CPUCACHE-MAXLEN/32 "_S(__LINE__));
		for(int i=0;i<MAXLEN;i+=32)
			pi[i] *= 3;
	}
	{
		FUNCTIME("CPUCACHE-MAXLEN/64 "_S(__LINE__));
		for(int i=0;i<MAXLEN;i+=64)
			pi[i] *= 3;
	}
	{
		FUNCTIME("CPUCACHE-MAXLEN/128 "_S(__LINE__));
		for(int i=0;i<MAXLEN;i+=128)
			pi[i] *= 3;
	}
	return 0;
}
