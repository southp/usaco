#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 3)
        return -1;

    int R = atoi(argv[1]);
    ofstream out(argv[2]);

    srand(time(0));
    out<<R<<endl;
    for(int i = 0; i < R; ++i)
    {
        for(int j = 0; j < i+1; ++j)
            out << rand() % 100 << " ";
        out<<endl;
    }
    return 0;
}
