/**
 * brief: gen some diffirent serials
 * author: jefftian
 * Date: Thu Dec 22 19:10:39 CST 2016
 */
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <set>

using namespace std;

static char Seeds[] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
    'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R',
    'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    '2', '3', '4', '5', '6', '7', '8', '9',
};
static const int SeedsCount = sizeof(Seeds)/sizeof(Seeds[0]);

static const int  MAX_SERIAL_LEN = 12;

//[min,max]
int randBetween(int min, int max)
{
    if(min == max) return min;

    if(min < max)
    {
        unsigned int distance = max - min + 1;
        unsigned int offset = rand()%distance;
        return min + offset;
    }

    return randBetween(max, min);
}
  
int main(int argc, char **argv)
{
    assert(MAX_SERIAL_LEN > 0);
    srand(time(0));
    unsigned int count = 10;
    if(argc > 0) count = atoi(argv[1]);

    std::set<std::string> serials;

    while(count)
    {
        char serial[MAX_SERIAL_LEN+1];
        for(int i = 0; i < MAX_SERIAL_LEN; ++i)
            serial[i] = Seeds[randBetween(0, SeedsCount-1)];
        if(serials.find(serial) != serials.end())
            continue;
        serials.insert(serial);
        -- count;
        cout<<serial<<endl;
    }
    return 0;
}
