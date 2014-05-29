/*
ID: southp01
TASK: milk2
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <list>

using namespace std;

struct Node
{
    Node() : head(false),val(0){}
    Node(bool h,int v = 0) : head(h), val(v){}
    bool head;
    int val;
};
typedef list<Node> Lin;
typedef Lin::iterator Lit;
const int NAM = -1000;

int main(int argc, char* argv[])
{
    int N;
    ifstream in;
    ofstream out("milk2.out");
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("milk2.in");
    }

    Lin milk;

    Node s1(true),s2;
    in >> N;
    while(in >> s1.val >> s2.val)
    {
        if(milk.empty())
        {
            //redundant node at the beginning and the end to simplify edge condition.
            milk.push_back(Node(false,NAM));
            milk.push_back(s1);
            milk.push_back(s2);
            milk.push_back(Node(true,2000000));
        }
        else
        {
            Lit s1lt,s2lt,it = milk.begin();
            for(; it != milk.end(); ++it)
            {
                Node& n = *it;
                if(n.val >= s1.val)
                {
                    s1lt = milk.insert(it,s1);
                    break;
                }
            }
            for(; it != milk.end(); ++it)
            {
                Node& n = *it;
                if(n.val > s2.val) //tricky part!
                {
                    s2lt = milk.insert(it,s2);
                    break;
                }
            }

            Lit lb = s1lt, rb = s2lt;
            --lb;
            ++rb;
            if(lb->head && !rb->head)
            {
                Lit it = s1lt;
                while(it != rb)
                {
                    milk.erase(it++);
                }
            }
            else if(lb->head && rb->head)
            {
                Lit it = s1lt;
                while(it != s2lt)
                {
                    milk.erase(it++);
                }
            }
            else if(!lb->head && !rb->head)
            {
                Lit it = s1lt;
                ++it;
                while(it != rb)
                {
                    milk.erase(it++);
                }
            }
            else
            {
                Lit it = s1lt;
                ++it;
                while(it != s2lt)
                {
                    milk.erase(it++);
                }
            }
        }
    }
    milk.pop_front();
    milk.pop_back();

    Lit it = milk.begin();
    int maxmilk = 0, maxhungry = 0;
    int prev = it->val;
    for(; it != milk.end(); ++it)
    {
        cout<<it->head<<"  "<<it->val<<endl;
        int cur = it->val, dm = cur - prev;
        if(it->head)
        {
            maxhungry = max(maxhungry,dm);
        }
        else
        {
            maxmilk = max(maxmilk,dm);
        }
        prev = cur;
    }
    cout << "solution: " << maxmilk << " " << maxhungry << endl;
    out << maxmilk << " " << maxhungry << endl;

    return 0;
}

