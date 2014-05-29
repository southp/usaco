/*
ID: southp01
LANG: C++
TASK: sprime
*/

#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int N;
ofstream out("sprime.out");

bool is_prime(int val)
{
    int sq = sqrt(val);
    for(int i = 2; i <= sq; ++i)
        if(val % i == 0)
            return false;
    return true;
}

void sprime(int i, int sum)
{
    if(i == N)
    {
        cout<<sum<<endl;
        out<<sum<<endl;
        return;
    }
    for(int d = 1; d <= 9; ++d)
    {
        if(i == 0 && d == 1)
            continue;
        if((d == 2 || d == 5) && i != 0)
            continue;
        int t = sum*10 + d;
        if(is_prime(t))
            sprime(i+1,t);
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("sprime.in");
    in >> N;
    sprime(0,0);

    return 0;
}
