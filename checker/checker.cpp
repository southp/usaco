/*
ID: southp01
LANG: C++
TASK: checker
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <climits>

using namespace std;

ofstream out("checker.out");
int N;
int row[14];
int nline = 0;
bool fullcol[14];
bool diag1[32];
bool diag2[32]; 

void checker(int r)
{
    if(r == N+1)
    {
        if(nline < 3)
        {
            for(int i = 1 ; i <=N; ++i)
            {
                cout<<row[i];
                out<<row[i];
                if(i != N)
                {
                    cout<<" ";
                    out<<" ";
                }
            }
            cout<<endl;
            out<<endl;
        }
        ++nline;
        return;
    }

    for(int c = 1; c <= N; ++c)
    {
        bool blocked = fullcol[c] || diag1[r-c+1+N] || diag2[r+c]; 
        if(!blocked)
        {
            row[r] = c;
            fullcol[c] = true;
            diag1[r-c+1+N] = true;
            diag2[r+c] = true;

            checker(r+1);
            
            fullcol[c] = false;
            diag1[r-c+1+N] = false;
            diag2[r+c] = false;
        }
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("checker.in");
    in >> N;
    memset(row,0,sizeof(row));
    row[0] = -INT_MAX;
    memset(fullcol,0,sizeof(fullcol));
    memset(diag1,0,sizeof(diag1));
    memset(diag2,0,sizeof(diag2));

    checker(1);
    cout<<nline<<endl;
    out<<nline<<endl;
    return 0;
}
