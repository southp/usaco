/*
ID: southp01
LANG: C++
TASK: milk3
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int cNum = 3;
int capa[cNum],vol[cNum];
bool p[20][20][20];
vector<int> result;

void pour()
{
    if(p[vol[0]][vol[1]][vol[2]])
        return;

    if(vol[0] == 0)
        result.push_back(vol[2]);
    
    p[vol[0]][vol[1]][vol[2]] = true;

    for(int i = 0; i < cNum; ++i)
    {
        if(vol[i] > 0)
        {
            for(int j = 0; j < cNum; ++j)
            {
                int vac = capa[j] - vol[j];
                if(vac > 0)
                {
                    int fill = min(vac,vol[i]);
                    vol[i] -= fill;
                    vol[j] += fill;
                    pour();
                    vol[i] += fill;
                    vol[j] -= fill;
                }
            }
        }
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("milk3.out");
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("milk3.in");
    }
    memset(vol,0,sizeof(vol));
    memset(p,0,sizeof(p));
    in >> capa[0] >> capa[1] >> capa[2];
#ifdef TEST
    cout<<"Capacity: "<<capa[0]<<" "<<capa[1]<<" "<<capa[2]<<endl;
#endif
    vol[2] = capa[2];

    pour();

    sort(result.begin(),result.end());
    for(int i = 0; i < result.size(); ++i)
    {
#ifdef TEST
        cout<<result[i];
        if(i != result.size() - 1)
            cout<<" ";
#endif
        out<<result[i];
        if(i != result.size() - 1)
            out<<" ";
    }
#ifdef TEST
    cout<<endl;
#endif
    out<<endl;
    return 0;
}
