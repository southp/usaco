/*
ID: southp01
TASK: namenum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string letter[] = {"","","ABC","DEF","GHI","JKL","MNO","PRS","TUV","XYZ"} ;
string curname;
bool found = false;
vector<string> names;
ofstream out("namenum.out");
void name_num(string n,int digit)
{
    if(digit == n.size())
    {
        vector<string>::iterator r = lower_bound(names.begin(),names.end(),curname);
        if(*r == curname)
        {
            found = true;
            out<<curname<<endl;
            cout<<curname<<endl;
        }
        return;
    }
    int d = static_cast<int>(n[digit] - '0');
    int nextdigit = digit + 1;
    string& lt = letter[d];
    curname[digit] = lt[0];
    name_num(n,nextdigit);
    curname[digit] = lt[1];
    name_num(n,nextdigit);
    curname[digit] = lt[2];
    name_num(n,nextdigit);
}

int main(int argc, char* argv[])
{
    string serial;
    if(argc == 2)
    {
        serial = argv[1];
    }
    else
    {
        ifstream in("namenum.in");
        in >> serial;
    }

    ifstream dict("dict.txt");
    string name;
    while(dict >> name)
    {
        names.push_back(name);
    }
    curname.resize(serial.size());
    name_num(serial,0);
    if(!found)
    {
        out<<"NONE"<<endl;
        cout<<"NONE"<<endl;
    }
    return 0;
}
