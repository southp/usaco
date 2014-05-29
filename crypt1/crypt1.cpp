/*
ID: southp01
TASK: crypt1
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> digits;
bool check(int n,int bd)
{
    int nd = 1;
    while(n)
    {
        if(nd > bd)
        {
            return false;
        }
        int r = n % 10;
        if(find(digits.begin(),digits.end(),r) == digits.end())
        {
            return false;
        }
        n /= 10;
        ++nd;
    }
    return true;
}

int main(int argc,char *argv[])
{
    ifstream in;
    ofstream out("crypt1.out");
    if(argc == 2)
    {
        in.open(argv[1]);
    }
    else
    {
        in.open("crypt1.in");
    }
    int N;
    in >> N;
    digits.resize(N);
    for(int i = 0; i < N; ++i)
    {
        in >> digits[i];
    }
#ifdef TEST
    for(int i = 0; i < N; ++i)
    {
        cout<<digits[i]<< " ";
    }
    cout<<endl;
#endif

    int total = 0;
    for(int k = 0; k < N; ++k)
    {
        for(int j = 0; j < N; ++j)
        {
            for(int i = 0; i < N; ++i)
            {
                int up = digits[k]*100+digits[j]*10+digits[i];
                for(int x = 0; x < N; ++x)
                {
                    for(int y = 0; y < N; ++y)
                    {
                        do
                        {
                            int row1 = digits[y]*up;
                            if(!check(row1,3))
                                break;
                            int row2 = digits[x]*up;
                            if(!check(row2,3))
                                break;
                            if(!check(row1+row2*10,4))
                                break;
#ifdef TEST
                            cout<<"Sol: "<<up<<" "<<digits[y]+digits[x]*10<<" "
                                <<row1<<" "<<row2<<" "<<row1+row2*10<<endl;
#endif
                            ++total;
                        }while(0);
                    }
                }
            }
        }
    }

    cout<<"Total: "<<total<<endl;
    out<<total<<endl;
    return 0;
}
