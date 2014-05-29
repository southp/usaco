/*
ID: southp01
LANG: C
TASK: runround
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGIT 9

int is_runround(unsigned int n)
{
    int digit[MAX_DIGIT];
    int touch[MAX_DIGIT];
    int nd = 0;
    int num = n;

    int i;

    memset(digit, 0, sizeof(touch));
    memset(touch, 0, sizeof(touch));

    while(num != 0)
    {
        digit[nd] = num % 10;
        num /= 10;
        ++nd;
    }

    i = nd - 1;
    while(1)
    {
        i = i - digit[i];
        while(i < 0)
            i += nd;
        i %= nd;

        if(touch[i])
            break;

        touch[i] = 1;
    }

    for(i = 0; i < nd; ++i)
    {
        if(!touch[i])
            return 0;
    }

    return 1;
}

int non_zero_unique(unsigned int n)
{
    int digit[10];
    int num = n;
    int d;

    memset(digit, 0, sizeof(digit));

    while(num != 0)
    {
        int d = num % 10;

        if(digit[d] || d == 0)
            return 0;

        digit[d] = 1;
        num /= 10;
    }

    return 1;
}

unsigned int find_runround(unsigned int start)
{
    unsigned int i;

    for(i = start; ; ++i)
    {
        if(non_zero_unique(i) && is_runround(i))
            return i;
    }

    return 0;
}

int main(int argc, char *argv[])
{
    FILE *in = NULL;
    FILE *out = fopen("runround.out", "w");

    unsigned int ans, start;

    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("runround.in", "r");

    fscanf(in, "%d", &start);

    ans = find_runround(start + 1);

    fprintf(out, "%d\n", ans);

    return 0;
}

