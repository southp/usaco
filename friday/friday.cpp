/*
ID: southp01
TASK: friday
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

int g_monthday[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int g_leapmonthday[] = {0,31,29,31,30,31,30,31,31,30,31,30,31};

int main(int argc, char* argv[])
{
    int numyears = 0;
    if(argc == 2)
    {
        sscanf(argv[1],"%d",&numyears);
    }
    else
    {
        ifstream in("friday.in");
        in >> numyears;
    }
    int count[7];
    memset(count,0,sizeof(count));

    int totaldays = 0;
    for(int dy = 0; dy < numyears; ++dy)
    {
        int curyear = 1900+dy;
        bool isleap = false;
        if(curyear % 100 == 0)
        {
            isleap = curyear % 400 == 0;
        } 
        else
        {
            isleap = curyear % 4 == 0;
        }
        totaldays += 13;
        for(int month = 1; month <= 12; ++month)
        {
            totaldays += (isleap? g_leapmonthday[month - 1]:g_monthday[month - 1]);
            count[totaldays % 7] += 1;
        }
        totaldays += 18;
    }
    ofstream out("friday.out");
    out << count[6] << " ";
    for(int i = 0; i < 5; ++i)
    {
        out << count[i] << " ";
    }
    out << count[5] << endl;
    return 0;
}

