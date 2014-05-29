/*
ID: southp01
TASK: packrec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <climits>

#define VFOR(v,body) for(size_t i = 0; i < v.size(); ++i) {body};

using namespace std;

struct Rect
{
    Rect():p(0),q(0){}
    Rect(int p,int q) : p(p),q(q){}
    int p,q;
};

int minarea = INT_MAX;
int totalarea = 0;
vector<Rect> rs;
vector<int> enrs(201);

//  q
//  ^
//  |
//(x,y) -> p

void insert(const Rect& r)
{
    int p,q;
    if(r.p > r.q)
    {
        p = r.q;
        q = r.p;
    }
    else
    {
        p = r.p;
        q = r.q;
    }
    int area = p*q;
    if(area < totalarea)
    {
        int* a = 0;
        cout<<"Impossible!"<<endl;
        *a = 0;
    }

    if(area < minarea)
    {
        VFOR(enrs, enrs[i] = 0;)
        minarea = area;
        enrs[p] = q;
    }
    else if(area == minarea)
    {
        enrs[p] = q;
    }
}

void pat1()
{
    int maxp = 0,maxq = 0;
    for(size_t i = 0; i < rs.size(); ++i)
    {
        maxp += rs[i].p;
        maxq = max(maxq,rs[i].q);
    }

    insert(Rect(maxp,maxq));
#ifdef TEST
    cout<<"Pat1: " << maxp << " " << maxq<<endl;
#endif
}

void pat2()
{
    int maxp = 0, maxq = 0, maxaddq = 0;
    for(size_t i = 1; i < rs.size(); ++i)
    {
        maxaddq = max(rs[i].q,maxaddq);
    }
    maxp = max(rs[0].p,rs[1].p+rs[2].p+rs[3].p);
    maxq = rs[0].q + maxaddq;
    insert(Rect(maxp,maxq));

#ifdef TEST
    cout<<"Pat2: " << maxp << " " << maxq<<endl;
#endif
}

void pat3()
{
    int maxp = rs[0].p + rs[1].p;
    if(rs[0].p < rs[2].p + rs[3].p)
    {
        maxp = rs[1].p + rs[2].p + rs[3].p;
    }

    int addq = rs[0].q + max(rs[2].q,rs[3].q);
    int maxq = max(rs[1].q,addq);
    insert(Rect(maxp,maxq));

#ifdef TEST
    cout<<"Pat3: " << maxp << " " << maxq<<endl;
#endif
}

void pat4()
{
    if(rs[3].p > rs[1].p)
        return;

    int maxp = 0, maxq = 0;
    maxp = rs[0].p + rs[1].p + rs[2].p;
    maxq = max(rs[0].q, max(rs[2].q, rs[1].q + rs[3].q));
    insert(Rect(maxp,maxq));
#ifdef TEST
    cout<<"Pat4: " << maxp << " " << maxq<<endl;
#endif
}

void pat5()
{
    if(rs[1].p > rs[0].p)
        return;

    int maxp = 0, maxq = 0;
    maxp = rs[0].p + rs[2].p + rs[3].p;
    maxq = max(rs[0].q+rs[1].q,max(rs[2].q,rs[3].q));
    insert(Rect(maxp,maxq));

#ifdef TEST
    cout<<"Pat5: " << maxp << " " << maxq<<endl;
#endif
}

void pat6()
{
    int maxp = rs[0].p+rs[1].p, maxq = 0;
    if(rs[2].p + rs[3].p > maxp)
        return;
    if(rs[0].q < rs[1].q)
    {
        if(rs[2].p > rs[0].p)
            return;
    }
    else if(rs[0].q > rs[1].q)
    {
        if(rs[3].p > rs[1].p)
            return;
    }
    maxq = max(rs[0].q+rs[2].q,rs[1].q+rs[3].q);
    insert(Rect(maxp,maxq));

#ifdef TEST
    cout<<"Pat6: " << maxp << " " << maxq<<endl;
#endif
}

void search_rot(int fidx)
{
    if(fidx == rs.size())
    {
        pat1();
        pat2();
        pat3();
        pat4();
        pat5();
        pat6();
        return;
    }

    search_rot(fidx + 1);
    swap(rs[fidx].p,rs[fidx].q);
    search_rot(fidx + 1);
    swap(rs[fidx].p,rs[fidx].q);
}

void search(int fidx)
{
    if(fidx == rs.size())
    {
        search_rot(0);
        return;
    }

    for(int i = fidx; i < rs.size(); ++i)
    {
        //search(fidx + 1);
        swap(rs[fidx],rs[i]);
        search(fidx + 1);
        swap(rs[fidx],rs[i]);
    }
}

int main(int argc, char* argv[])
{
    ifstream in;
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("packrec.in");
    }
    rs.resize(4);
    VFOR(rs,
            in >> rs[i].p >> rs[i].q;
            totalarea += rs[i].p*rs[i].q;
            )
       
#ifdef TEST
    cout<<"Input: "<<endl;
    VFOR(rs,
        cout<<rs[i].p<<" "<<rs[i].q<<endl;
    )
#endif
    search(0);

#ifdef TEST
    if(!enrs.empty())
        cout<<minarea<<endl;
    VFOR(enrs,
        if(enrs[i] != 0)
            cout<<i<<" "<<enrs[i]<<endl;
    )
#endif
    ofstream out("packrec.out");
    if(!enrs.empty())
        out<<minarea<<endl;
    VFOR(enrs,
        if(enrs[i] != 0)
            out<<i<<" "<<enrs[i]<<endl;
    )
    return 0;
}

