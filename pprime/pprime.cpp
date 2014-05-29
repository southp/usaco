/*
ID: southp01
LANG: C++
TASK: pprime
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
using namespace std;

typedef unsigned int Word;

int a,b;
Word buf[100000000 / 32 + 1];

void set(int idx)
{
    int num_byte = idx / 32,
        rest = idx % 32;
    buf[num_byte] |= 1 << rest;
}

bool get(int idx)
{
    int num_byte = idx / 32,
        rest = idx % 32;
    return buf[num_byte] & (1 << rest);
}

bool is_pal(int n)
{
    char buf[32];
    sprintf(buf,"%d",n);
    int len = strlen(buf);
    char *p = buf, *q = buf+len-1;
    for(;p < q; ++p, --q)
    {
        if(*p != *q)
            return false;
    }
    return true;
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("pprime.out");
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("pprime.in");
    in >> a >> b;
    memset(buf,0,sizeof(buf));

    int p = 2;
    while(p <= b)
    {
        /*
        if(p >= a && is_pal(p))
        {
#ifdef TEST
            cout<<p<<endl;
#endif
            out<<p<<endl;
        }
        */

        for(int i = 1, n = p*i; n <= b; ++i, n = p*i)
            set(n);

        while(get(++p));
    }
    return 0;
}

