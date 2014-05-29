/*
ID: southp01
TASK: beads
LANG: C++
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#ifdef TEST
#define OUT cout
#else
#define OUT out
ofstream out("beads.out");
#endif

int len = 0;
string necklace;

int circular_mod(int idx, int len)
{
    while(idx < 0)
    {
        idx += len;
    }
    return idx % len;
}

int collect(int idx, int dir)
{
    int next = idx;
    if(dir == -1)
    {
        next = circular_mod(idx-1,len);
    }
    int n = 0;
    char pickcolor = 'w';
    while(n < len)
    {
        char nextcolor = necklace[next];
        if(nextcolor != 'w' && nextcolor != pickcolor)
        {
            if(pickcolor == 'w')
            {
                pickcolor = nextcolor;
            }
            else
            {
                break;
            }
        }
        ++n;
        next = circular_mod(next+dir,len);
    }
    return n;
}

int main(int argc,char* argv[])
{
    if(argc == 2)
    {
        ifstream in(argv[1]);
        in >> len >> necklace;
    }
    else
    {
        ifstream in("beads.in");
        in >> len >> necklace;
    }
    cout<<"INPUT: "<<necklace<<endl;

    int maxbeads = 0;
    int maxbp = 0;
    for(int i = 0; i < len; ++i)
    {
        int curbeads = collect(i,1) + collect(i,-1);
        curbeads = min(curbeads,len);
        if(curbeads > maxbeads)
        {
            maxbeads = curbeads;
            maxbp = i;
        }
    }

    cout << "break point: " << maxbp << endl;
    OUT << maxbeads << endl;

    return 0;
}

