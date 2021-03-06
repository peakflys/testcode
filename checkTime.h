#ifndef _FUNCTIONTIME_H
#define _FUNCTIONTIME_H

#include <iostream>
#include <time.h>
class FunctionTime
{
	public:
		FunctionTime(const std::string &_func) : func(_func)
		{
			clock_gettime(CLOCK_REALTIME,&tv_begin);//when build, you should add -lrt
		}
		~FunctionTime()
		{
			struct timespec tv_end;
			clock_gettime(CLOCK_REALTIME,&tv_end);
			unsigned long end = tv_end.tv_sec*1000000000 + tv_end.tv_nsec;
			unsigned long begin = tv_begin.tv_sec*1000000000 + tv_begin.tv_nsec;
			std::cout<<func<<" cost time: "<<(end-begin)/1000000<<std::endl;
		}
	private:
		std::string func;
		struct timespec tv_begin;
};
#define FUNCTIME(func) FunctionTime funcTime(func)
#define _TY(x) #x
#define _S(x) _TY(x)

#endif
