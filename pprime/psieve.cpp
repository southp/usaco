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

const int cMax = 100000000;
Word buf[cMax / 32 + 1];

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

int main(int argc, char* argv[])
{
    memset(buf,0,sizeof(buf));

    int p = 2;
    while(p <= cMax)
    {
        for(int i = 2, n = p*i; n <= cMax; ++i, n = p*i)
            set(n);
        while(get(++p));
    }
    ofstream ppr("prime_pp");
    ppr << "int cMax = 100000000;\nWord buf[] = {\n";
    for(int i = 0; i < cMax / 32; ++i)
    {
        ppr << "0x" << hex << buf[i];
        if(i != cMax/32 - 1)
            ppr <<",";
        if(i % 8 == 0 && i != 0)
            ppr << endl;
    }
    ppr << "};\n" << endl;
    return 0;
}

