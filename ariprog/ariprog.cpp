/*
ID: southp01
LANG: C++
TASK: ariprog
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <utility>

using namespace std;

int N,M;
const int cSize = 62500+62500+1;
bool bsqt[cSize];
vector<int> bsqv;
typedef pair<int,int> pii;

bool comp(const pii& a, const pii& b)
{
    if(a.second < b.second)
    {
        return true;
    }
    else if(a.second > b.second)
    {
        return false;
    }
    else
    {
        return a.first < b.first;
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("ariprog.out");
    if(argc == 2)
        in.open(argv[1]);
    else
        in.open("ariprog.in");

    in >> N >> M;
    memset(bsqt,0,sizeof(bsqt));
    for(int p = 0; p <= M; ++p)
        for(int q = p; q <= M; ++q)
        {
            int bsq = p*p + q*q;
            if(!bsqt[bsq])
            {
                bsqt[bsq] = true;
                bsqv.push_back(bsq);
            }
        }
#ifdef TEST
    cout<<"Total bsq: "<<bsqv.size()<<endl;
#endif

    sort(bsqv.begin(),bsqv.end());
    bool ever = false;
    vector<pii> result;
    for(int i = 0; i < bsqv.size(); ++i)
    {
        int a = bsqv[i];
        for(int j = i+1; j < bsqv.size(); ++j)
        {
            int b = bsqv[j] - a;
            if(b > 0)
            {
                bool pass = true;
                for(int n = 1; n < N; ++n)
                {
                    int next = a+n*b;
                    if(next >= cSize || !bsqt[next])
                    {
                        pass = false;
                        break;
                    }
                }
                if(pass)
                {
                    result.push_back(make_pair(a,b));
                }
            }
        }
    }
    if(!result.empty())
    {
        sort(result.begin(),result.end(),comp);
        for(int i = 0; i < result.size(); ++i)
        {
#ifdef TEST
            cout<<result[i].first<<" "<<result[i].second<<endl;
#endif
            out<<result[i].first<<" "<<result[i].second<<endl;
        }
    }
    else
    {
#ifdef TEST
        cout<<"NONE"<<endl;
#endif
        out<<"NONE"<<endl;
    }
    return 0;
}
