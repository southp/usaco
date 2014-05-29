/*
ID: southp01
LANG: C++
TASK: numtri
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>

using namespace std;

int R = 0;
vector<int> t;
vector<int> sumtab;

int index(int r, int c)
{
    return (r+1)*r/2 + c;
}

int hit = 0;
int thit = 0;
int dfs(int r, int c, int sum)
{
    int idx = index(r,c);
    if(sumtab[idx] != -1)
    {
        ++thit;
        return sumtab[idx];
    }
    else
    {
        ++hit;
        if(r == R - 1)
        {
            return t[idx];
        }
        int mymax = t[idx] + max(dfs(r+1,c,sum),dfs(r+1,c+1,sum));
        sumtab[idx] = mymax;
        return mymax;
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("numtri.out");
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("numtri.in");
    
    in >> R;
    int total = R*(R+1)/2;
    t.resize(total);
    sumtab.resize(total);
    for(int i = 0; i < R; ++i)
        for(int j = 0; j < i+1; ++j)
        {
            int idx = index(i,j);
            in >> t[idx];
            sumtab[idx] = -1;
        }

    int maxsum = dfs(0,0,0);
#ifdef TEST
    cout<<"Ans: "<<maxsum<<endl;
    cout<<"Hit count: "<<hit<<endl;
    cout<<"Table hit count: "<<thit<<endl;
#endif
    out<<maxsum<<endl;
    return 0;
}
