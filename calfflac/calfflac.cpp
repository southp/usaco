/*
ID: southp01
TASK: calfflac
LANG: C++
*/

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool is_pal_sub(const string& str,int beg, int len)
{
    int half = len / 2;
    for(int i = 0; i < half; ++i)
    {
        if(str[i + beg] != str[beg + len - i - 1])
        {
            return false;
        }
    }
    return true;
}

int find_pal(const string& str,int len)
{
    int size = str.size();
    for(int i = 0; i + len <= size; ++i)
    {
        if(is_pal_sub(str,i,len))
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char* argv[])
{
    ifstream in;
    ofstream out("calfflac.out");
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("calfflac.in");
    }

    string content;
    //read-in all content
    in.seekg(0,ios::end);
    int size = in.tellg();
    in.seekg(0,ios::beg);
    content.resize(size);
    in.read(&content[0],size);
    cout<<"Original: "<<content<<endl;
    
    //transform: check result & map
    string trans;
    vector<int> idxtab;
    idxtab.resize(size);
    for(int i = 0,j = 0; i < size; ++i)
    {
        string::value_type c = content[i];
        if(isalpha(c))
        {
            trans.push_back(static_cast<string::value_type>(tolower(c)));
            idxtab[j] = i;
            ++j;
        }
    }

#ifdef TEST
    cout<<"Trans: "<<trans<<endl;
    cout<<"Mapping: "<<endl;
    for(int i = 0; i < trans.size(); ++i)
    {
        cout<<idxtab[i]<<" ";
    }
    cout<<endl;
    
    cout<< "1: " << is_pal_sub("abcdeffedcba",0,12) << endl;
    cout<< "1: " << is_pal_sub("abcccccccezx",2,7) << endl;
    cout<< "2: " << find_pal("abcccccccezx",7) << endl;
    cout<< "-1: " << find_pal("abcccccccezx",8) << endl;
    cout<< "0: " << find_pal("flhqjhwjq",1) << endl;
    cout<< "15: " << find_pal("confuciussaymadamimadam",11) << endl;
#endif
    //compute palindrome
    int len = min(2000,(int)trans.size());
    int beg = -1;
    while(len)
    {
        beg = find_pal(trans,len);
        if(beg != -1)
        {
            break;
        }
        --len;
    }

    cout<<content<<endl;
    cout<<"BEG:LEN: "<<beg<<","<<len<<endl;
    out<<len<<endl;
    for(int i = idxtab[beg]; i <= idxtab[beg+len-1]; ++i)
    {
        cout<<content[i];
        out<<content[i];
    }
    cout<<endl;
    out<<endl;
    return 0;
}
