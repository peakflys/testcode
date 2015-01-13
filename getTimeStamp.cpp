#include <iostream>
using namespace std;

bool getTimeFromTimeStamp( time_t time, char* date )
{
    struct tm stTime;
    struct tm *pstTime = localtime_r(&time, &stTime);
	if(NULL == pstTime)
        return false;

    //asctime(&stTime) can give default formate time
    sprintf(date, "%04d-%02d-%02d %02d:%02d:%02d", stTime.tm_year + 1900, stTime.tm_mon + 1, stTime.tm_mday, stTime.tm_hour, stTime.tm_min, stTime.tm_sec);
    
    return true;
}

int main(int argc, char** argv)
{
    if(argc == 1)
        cout<<"now time stamp is: "<<time(0)<<endl;
    else if(argc == 2)
    {
        time_t stamp = atoi(argv[1]);
        char timeString[32];
        if(!getTimeFromTimeStamp(stamp, timeString))
        {
            cout<<"timestamp: "<<stamp<<" is invalid"<<endl;
            return 0;
        }
        cout<<"timestamp("<<stamp<<")"<<" formate: "<<timeString<<endl;
    }
    else
        cout<<"input invalid!"<<endl;
    return 0;
}
