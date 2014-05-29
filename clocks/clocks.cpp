/*
ID: southp01
TASK: clocks
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

char all12[3][3];
struct Clock
{
    Clock()
    {
        memset(t,0,sizeof(t));
    }
    Clock(const Clock& c)
    {
        memcpy(t,c.t,sizeof(t));
    }
    bool is12()
    {
        return memcmp(t,all12,sizeof(t)) == 0;
    }

    char t[3][3];
};

void add_clock(Clock& a, Clock& b)
{
    for(int i=0; i < 3; ++i)
        for(int j=0; j < 3; ++j)
        {
            a.t[i][j] += b.t[i][j];
            if(a.t[i][j] > 12)
            {
                a.t[i][j] %= 12;
            }
        }
}

Clock clk;
Clock op[9];
vector<char> minseq;
char pp[] = {0,0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,8,8,8,9,9,9};
const int cSize = sizeof(pp)/sizeof(char);

bool check(vector<char>& seq)
{
#ifdef TEST
    cout<<"test seq: "<<endl;
    for(int i = 0; i < seq.size(); ++i)
    {
        cout<<static_cast<int>(seq[i])<<" ";
    }
    cout<<endl;
#endif

    Clock t(clk);
    if(t.is12())
        return true;

    for(int i = 0; i < seq.size(); ++i)
    {
        add_clock(t, op[seq[i] - 1]);
    }
    return t.is12();
}

vector<char> seq;
bool tdfs(int nleft,int beg)
{
    if(nleft == 0)
        return check(seq);

    char pick = -1;
    for(int i = beg; i < cSize; ++i)
    {
        if(pick != pp[i])
        {
            char old = seq[nleft-1];

            seq[nleft-1] = pp[i];
            if(tdfs(nleft-1,i+1))
                return true;
            seq[nleft-1] = old;

            pick = pp[i];
        }
    }

    return false;
}

void align()
{
    for(int i = 0; i < cSize; ++i)
    {
        seq.clear();
        seq.resize(i);
        if(tdfs(i,0))
        {
            minseq = seq;
            return;
        }
    }
}

void sc(Clock& c, int i, int j) //set clock 1
{
    c.t[i][j] = 3;
}

void init_op()
{
    sc(op[0],0,0); //A
    sc(op[0],0,1); //B
    sc(op[0],1,0); //D
    sc(op[0],1,1); //E

    sc(op[1],0,0); //A
    sc(op[1],0,1); //B
    sc(op[1],0,2); //C
    
    sc(op[2],0,1); //B
    sc(op[2],0,2); //C
    sc(op[2],1,1); //E
    sc(op[2],1,2); //F

    sc(op[3],0,0); //A
    sc(op[3],1,0); //D
    sc(op[3],2,0); //G

    sc(op[4],0,1); //B
    sc(op[4],1,0); //D
    sc(op[4],1,1); //E
    sc(op[4],1,2); //F
    sc(op[4],2,1); //H

    sc(op[5],0,2); //C
    sc(op[5],1,2); //F
    sc(op[5],2,2); //I

    sc(op[6],1,0); //D
    sc(op[6],1,1); //E
    sc(op[6],2,0); //G
    sc(op[6],2,1); //H

    sc(op[7],2,0); //G
    sc(op[7],2,1); //H
    sc(op[7],2,2); //I

    sc(op[8],1,1); //E
    sc(op[8],1,2); //F
    sc(op[8],2,1); //H
    sc(op[8],2,2); //I
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("clocks.out");
    if(argc == 2)
        in.open(argv[1]);

    else
        in.open("clocks.in");

    if(!in)
    {
        cerr << "No input file!" << endl;
        return -1;
    }

    for(int i = 0; i < 3; ++i)
        for(int j = 0; j < 3; ++j)
        {
            int v;
            in >> v;
            clk.t[i][j] = static_cast<char>(v);
            all12[i][j] = 12;
        }

    init_op();
    align();
    sort(minseq.begin(),minseq.end());

#ifdef TEST
    cout<<"Solution: ";
    for(size_t i = 0; i < minseq.size(); ++i)
    {
        cout<<static_cast<int>(minseq[i]);
        if(i != minseq.size()-1)
        {
            cout <<" ";
        }
    }
    cout<<endl;
#endif

    for(size_t i = 0; i < minseq.size(); ++i)
    {
        out<<static_cast<int>(minseq[i]);
        if(i != minseq.size()-1)
        {
            out <<" ";
        }
    }
    out<<endl;

    return 0;
}

