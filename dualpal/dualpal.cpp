/*
ID: southp01
TASK: dualpal
LANG: C++
*/

#include <stdio.h>
#include <string.h>

const char* map = "0123456789";
void convert(int n,char* str,int base)
{
    int digit = 0;
    int len = 1,t = n;
    while(t /= base)
    {
        ++len;
    }
    while(n)
    {
        str[len - 1 - digit++] = map[n % base];
        n = n / base;
    }
    str[digit] = '\0';
}

bool check(char* str)
{
    int len = strlen(str);
    for(int i = 0; i < len/2; ++i)
    {
        if(str[i] != str[len - i - 1])
        {
            return false;
        }
    }
    return true;
}

FILE* out = fopen("dualpal.out","w");
int main(int argc, char* argv[])
{
    int n,s;
    if(argc == 3)
    {
        sscanf(argv[1],"%d",&n);
        sscanf(argv[2],"%d",&s);
    }
    else
    {
        FILE* in = fopen("dualpal.in","r");
        fscanf(in,"%d %d",&n,&s);
    }

    for(int i = s+1; n > 0; ++i)
    {
        char ns[32];
        int ispal = 0;
        for(int b = 2; b <= 10; ++b)
        {
            convert(i,ns,b);
            if(check(ns))
            {
                ++ispal;
            }

            if(ispal >= 2)
            {
                printf("%d\n",i);
                fprintf(out,"%d\n",i);
                --n;
                break;
            }
        }
    }
    return 0;
}

