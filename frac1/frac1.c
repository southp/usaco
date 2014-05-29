/*
ID: southp01
LANG: C
TASK: frac1
*/

#include <stdio.h>
#include <string.h>

#define MAX_D 160

struct frac
{
    int n; /* numerator */
    int d; /* denominator */
    float val;
};

int cmp_frac(const void *a, const void* b)
{
    const struct frac* fa = a;
    const struct frac* fb = b;

    float diff = fb->val - fa->val;
    if(diff > 0.0f)
    {
        return -1;
    }
    else if(diff < 0.0f)
    {
        return 1;
    }
    else if(diff < 10e-6 && diff > -10e-6)
    {
        return 0;
    }
    
}


struct frac sol[MAX_D * MAX_D + 1];
int sol_count = 0;

int N;
int seive[MAX_D + 1][MAX_D + 1];

int main(int argc, char* argv[])
{
    FILE* in;
    FILE* out = fopen("frac1.out", "w");
    int d, n, i;

    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("frac1.in", "r");

    fscanf(in, "%d", &N);
    
    printf("N: %d\n", N);

    memset(sol, 0, sizeof(sol));
    memset(seive, 0, sizeof(seive));

    for(d = 1; d <= N; ++d)
    {
        for(n = 0; n <= d; ++n)
        {
            int mul_d = d, mul_n = n;
            int mul = 1;

            if(!seive[d][n])
            {
                sol[sol_count].d = d;
                sol[sol_count].n = n;
                sol[sol_count].val = (float)n / (float)(d);

                ++sol_count;
            }
            while(mul_d <= N)
            {
                seive[mul_d][mul_n] = 1;

                ++mul;
                mul_d = d*mul;
                mul_n = n*mul;
            }
        }
    }

    qsort(sol, sol_count, sizeof(struct frac), cmp_frac);

    for(i = 0; i < sol_count; ++i)
    {
        struct frac* f = &sol[i];
        printf("%d/%d\n", f->n, f->d);
        fprintf(out, "%d/%d\n", f->n, f->d);
    }

    return 0;
}
