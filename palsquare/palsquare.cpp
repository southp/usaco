/*
ID: southp01
TASK: palsquare
LANG: C++
*/

#include <stdio.h>
#include <string.h>

const char* map = "0123456789ABCDEFGHIJ";
int base = 0;
void convert(int n,char* str)
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

int main(int argc,char* argv[])
{
    if(argc == 2)
    {
        sscanf(argv[1],"%d",&base);
    }
    else
    {
        FILE* in = fopen("palsquare.in","r");
        fscanf(in,"%d",&base);
        fclose(in);
    }
    
    FILE* out = fopen("palsquare.out","w");
    for(int i = 1; i <= 300; ++i)
    {
        char ns[32],sqs[32];
        int sqi = i*i;
        convert(sqi,sqs);
        if(check(sqs))
        {
            convert(i,ns);
            printf("%s %s\n",ns,sqs);
            fprintf(out,"%s %s\n",ns,sqs);
        }
    }

    fclose(out);
    return 0;
}
