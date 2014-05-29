/*
ID: southp01
TASK: milk
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

typedef pair<int,int> Pii;
typedef vector<Pii> Vii;

bool compare_f(const Pii& a, const Pii& b)
{
    return a.first < b.first;
}

int main(int argc, char* argv[])
{
    ofstream out("milk.out");
    ifstream in;
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("milk.in");
    }
    int total = 0, nf = 0;
    in >> total >> nf;
    Vii fs;
    fs.resize(nf);
    for(int i = 0; i < nf; ++i)
    {
        Pii &f = fs[i];
        in >> fs[i].first >> fs[i].second;
    }
    sort(fs.begin(),fs.end(),compare_f);
    int cur = 0, sum = 0;
    while(total)
    {
        Pii &f = fs[cur];
        int np = min(total,f.second);
        sum += np * f.first;
        total -= np;
        ++cur;
    }
    cout << sum << endl;
    out << sum << endl;

    return 0;
}
