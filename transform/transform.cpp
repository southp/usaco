/*
ID: southp01
TASK: transform
LANG: C++
*/

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
typedef char (M)[100 + 1];
M a,b;

void rotate(M& m)
{
    M t;
    memset(t,0,sizeof(t));
    for(int j = 0; j < N; ++j)
    {
        for(int i = 0; i < N; ++i)
        {
            t[N-j-1+i*N] = m[i+j*N];
        }
    }
    memcpy(m,t,sizeof(M));
}

void reflect(M& m)
{
   for(int j = 0; j < N; ++j)
   {
       for(int i = 0; i < N/2; ++i)
       {
           swap(m[i + j*N],m[N-i-1 + j*N]);
       }
   }
}

void print_M(M& m)
{
    for(int j = 0; j < N; ++j)
    {
        for(int i = 0; i < N; ++i)
        {
            printf("%c ",m[i + j*N]);
        }
        printf("\n");
    }
}

FILE* out = fopen("transform.out","w");
void output(const char* str)
{
    printf("%s\n",str);
    fprintf(out,"%s\n",str);
}

int main(int argc, char* argv[])
{
    size_t msize = sizeof(M);
    memset(a,0,msize);
    memset(b,0,msize);
    FILE* in;
    if(argc == 2)
    {
        in = fopen(argv[1],"r");
    }
    else
    {
        in = fopen("transform.in","r");
    }
    fscanf(in,"%d",&N);
    printf("Dimension: %d\n",N);
    for(int j = 0; j < N; ++j)
    {
        fscanf(in,"%s",(a+j*N));
    }
    for(int j = 0; j < N; ++j)
    {
        fscanf(in,"%s",(b+j*N));
    }
    fclose(in);
    printf("Input a:\n");
    print_M(a);
    printf("Input b:\n");
    print_M(b);

    M c;
    memcpy(c,a,sizeof(c));
    /*
    printf("Before: \n");
    print_M(c);
    */
    rotate(c);
    /*
    printf("After: \n");
    print_M(c);
    */
    if(memcmp(b,c,msize) == 0)
    {
        output("1");
        return 0;
    }
    rotate(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("2");
        return 0;
    }
    rotate(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("3");
        return 0;
    }
    memcpy(c,a,sizeof(c));
    reflect(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("4");
        return 0;
    }
    rotate(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("5");
        return 0;
    }
    rotate(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("5");
        return 0;
    }
    rotate(c);
    if(memcmp(b,c,msize) == 0)
    {
        output("5");
        return 0;
    }
    if(memcmp(b,a,msize) == 0)
    {
        output("6");
        return 0;
    }
    output("7");

    fclose(out);
    return 0;
}

