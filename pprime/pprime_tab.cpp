/*
ID: southp01
LANG: C++
TASK: pprime
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;

int a,b;
ofstream out;

bool is_prime(int val)
{
    int sq = (int)(sqrt(val));
    for(int i = 2; i <= sq; ++i)
    {
        if(val % i == 0)
            return false;
    }
    return true;
}

char dbuf[16];
void palnum(int i, int nd)
{
    int mod = nd % 2, div = nd/2;
    if(i == (mod == 0? div : (div + 1)))
    {
        size_t len = strlen(dbuf);
        int val = 0;
        if(mod == 0)
        { 
            size_t len = strlen(dbuf);
            for(int x = len-1, z = len; x >= 0; --x, ++z)
            {
                dbuf[z] = dbuf[x];
            }
#ifdef TEST
            cout<<strlen(dbuf)<<": "<<dbuf<<endl;
#endif
        }
        else
        {
            if(nd == 1)
            {
#ifdef TEST
                cout<<dbuf<<endl;
#endif
            }
            else
            {
                for(int x = len-2, z = len; x >= 0; --x, ++z)
                {
                    dbuf[z] = dbuf[x];
                }
#ifdef TEST
                cout<<strlen(dbuf)<<": "<<dbuf<<endl;
#endif
            }
        }
        sscanf(dbuf,"%d",&val);
        if(val >=a && val <= b && is_prime(val))
        {
#ifdef TEST
            cout<<"Sol: "<<val<<endl;
#endif
            out<<val<<endl;
        }
        dbuf[len] = '\0';
        return;
    }

    for(char d = '0'; d <= '9'; ++d)
    {
        if(d == '0' && i == 0 && nd != 1)
            continue;

        if(i == 0 && d % 2 == 0)
            continue;

        dbuf[i] = d;
        palnum(i+1,nd);
    }
}


int main(int argc, char* argv[])
{
    ifstream in;
    out.open("pprime.out");
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("pprime.in");
    in >> a >> b;

    int mindigit = 0,maxdigit = 0;
    char ibuf[32];
    sprintf(ibuf,"%d",a);
    mindigit = strlen(ibuf);
    sprintf(ibuf,"%d",b);
    maxdigit = strlen(ibuf);
    cout<<"digit number range: "<<mindigit<<" "<<maxdigit<<endl;
    for(int n = mindigit; n <= maxdigit; ++n)
    {
        memset(dbuf,0,sizeof(dbuf));
        palnum(0,n);
    }

    return 0;
}
