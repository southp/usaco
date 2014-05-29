/*
ID: southp01
LANG: C
TASK: sort3
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NUM 1000

int step = 0;
int N;
int   count[3 + 1];
int prescan[3 + 2];
int       r[MAX_NUM];

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;

    ++step;
}

int find(int beg, int end, int val)
{
    int i;
    for(i = beg; i != end; ++i)
    {
        if(r[i] == val)
            break;
    }

    return i;
}

void swap_segment(int from, int to)
{
    printf("*** seg: %d - %d ***\n", from, to);
    int i = prescan[from], iend = prescan[from + 1];
    int j = prescan[to], jend = prescan[to + 1];

    while(i != iend && j != jend)
    {
        i = find(i, iend, to);
        if(i != iend)
        {
            j = find(j, jend, from);
            
            if(j != jend)
            {
                printf("swap: i%d:%d, i%d:%d \n", i, r[i], j, r[j]);
                swap(r+i, r+j);
            }
        }
    }
}

void find_sort()
{
    int i, iend;
    int v;

    swap_segment(1, 2);
    swap_segment(1, 3);
    swap_segment(2, 3);

    printf("First run: \n");
    for(i = 0; i < N; ++i)
        printf("%d ", r[i]);
    printf("\n");

    for(v = 1; v < 3; ++v)
    {
        int i = prescan[v], iend = prescan[v+1];
        for(; i != iend; ++i)
        {
            if(r[i] != v)
            {
                int j = find(iend, N, v);
                assert(j != N);
                printf("swap: i%d:%d, i%d:%d \n", i, r[i], j, r[j]);
                swap(r+i, r+j);
            }
        }
    }

    printf("Final run: \n");
    for(i = 0; i < N; ++i)
        printf("%d ", r[i]);
    printf("\n");
}

int main(int argc, char* argv[])
{
    FILE* in;
    FILE* out = fopen("sort3.out", "w");
    int i;

    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("sort3.in", "r");

    memset(r, 0, sizeof(r));
    memset(count, 0, sizeof(count));

    fscanf(in, "%d", &N);
    for(i = 0; i < N; ++i)
        fscanf(in, "%d", r+i);

    printf("N: %d\n", N);
    for(i = 0; i < N; ++i)
        printf("%d ", r[i]);
    printf("\n");
    
    /* counting */
    for(i = 0; i < N; ++i)
        ++count[r[i]];

    /* printf("count: \n"); */
    /* for(i = 1; i <=3; ++i) */
    /*     printf("%d ", count[i]); */
    /* printf("\n"); */

    /* prescan. A trailing sum for convenience */
    for(i = 1; i <= 4; ++i)
        prescan[i] = prescan[i-1] + count[i-1]; 

    /* printf("prescan: \n"); */
    /* for(i = 1; i <= 4; ++i) */
    /*     printf("%d ", prescan[i]); */
    /* printf("\n\n"); */
    
    find_sort();

    printf("%d\n", step);
    fprintf(out, "%d\n", step);

    return 0;
}

