/*
ID: southp01
TASK: gift1
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char* argv[])
{
    ifstream in;
    if(argc < 2)
    {
        in.open("gift1.in");
    }

    int np = 0;
    in >> np;
    map<string,int> account;
    vector<string> order;
    for(int i = 0; i < np; ++i)
    {
        string name;
        in >> name;
        account.insert(make_pair(name,0));
        order.push_back(name);
    }

    while(in)
    {
        int initmoney = 0, ng = 0, gift = 0;
        string giver,receiver;
        in >> giver;
        in >> initmoney >> ng;
       
        map<string,int>::iterator giveraccount = account.find(giver);
        gift = ng == 0? 0 : initmoney / ng;
        //giveraccount->second += ng == 0? initmoney : initmoney % ng;
        for(int i = 0; i < ng; ++i)
        {
            in >> receiver;
            account[receiver] += gift;
            giveraccount->second -= gift;
        }
    }

    ofstream out("gift1.out");
    vector<string>::iterator end = order.end();
    for(vector<string>::iterator it = order.begin(); it != end; ++it)
    {
        //cout<<*it<<" "<<account[*it]<<endl;
        out<<*it<<" "<<account[*it]<<endl;
    }

    return 0;
}

