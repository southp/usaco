/*
ID: southp01
LANG: C
TASK: hamming
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int N, B, D;

int count = 0;
int r[256];

int hamm_dist(int a, int b)
{
    int ex = a ^ b;
    int i, dist = 0;

    for(i = 0; ex != 0 && i < B; ++i)
    {
        if(ex & 1)
            ++dist;

        ex >>= 1;
    }
    return dist;
}

int main(int argc, char* argv[])
{
    FILE* in, *out = fopen("hamming.out", "w");
    int cand = -1, max_cand;
    int i, j;

    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("hamming.in", "r");

    fscanf(in, "%d %d %d", &N, &B, &D);
    memset(r, 0, sizeof(r));
    max_cand = pow(2, B);

    do
    {
        int i, pass = 1;

        ++cand;

        for(i = 0; i < count; ++i)
        {
            if(hamm_dist(cand, r[i]) < D)
            {
                pass = 0;
                break;
            }
        }

        if(pass)
        {
            r[count] = cand;
            ++count;
        }
    }while(cand <= max_cand && count < N);

    for(i = 1; i <= count; ++i)
    {
        printf("%d", r[i-1]);
        fprintf(out, "%d", r[i-1]);

        if(i % 10 == 0)
        {
            printf("\n");
            fprintf(out, "\n");
        }
        else if(i < count)
        {
            printf(" ");
            fprintf(out, " ");
        }
        else if(i == count)
        {
            printf("\n");
            fprintf(out, "\n");
        }
    }

    return 0;
}
