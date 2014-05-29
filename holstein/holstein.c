/*
ID: southp01
LANG: C
TASK: holstein
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int V, G;
int vit[25 + 1];
int feed[15 + 1][25 + 1];

int min_scoop = INT_MAX;
int min_combi[15 + 1];

int combi[15 + 1];
int vit_rem[25 + 1];

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
void vit_add(int *a, int *b)
{
    int i;
    
    for(i = 0; i < V; ++i)
    {
        *(a+i) += *(b+i);
    }
}

void vit_sub(int *a, int *b)
{
    int i;
    
    for(i = 0; i < V; ++i)
    {
        *(a+i) -= *(b+i);
    }
}

void find_combi(int beg, int step, int k)
{
    int i;

    if(min_scoop != INT_MAX)
        return;

    if(k == 0)
    {
        for(i = 0; i < V; ++i)
        {
            if(vit_rem[i] > 0)
                return;
        }

        min_scoop = step;
        memcpy(min_combi, combi, sizeof(min_combi));
        return;
    }

    for(i = beg; i < G; ++i)
    {
        int old_step = combi[step];

        vit_sub(vit_rem, feed[i]);
        combi[step] = i;

        find_combi(i+1, step+1, k-1);

        vit_add(vit_rem, feed[i]);
        combi[step] = old_step;
    }
}

void healthy()
{
    int i;
    for(i = 1; i <= G; ++i)
    {
        memcpy(vit_rem, vit, sizeof(vit_rem));
        find_combi(0, 0, i);

        if(min_scoop != INT_MAX)
            break;
    }
}

int main(int argc, char* argv[])
{
    int i, j;
    FILE *in, *out = fopen("holstein.out", "w");
    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("holstein.in", "r");

    memset(vit, 0, sizeof(vit));
    memset(feed, 0, sizeof(feed));
    memset(combi, 0, sizeof(combi));

    fscanf(in, "%d", &V);
    for(i = 0; i < V; ++i)
        fscanf(in, "%d", vit+i);

    fscanf(in, "%d", &G);
    for(i = 0; i < G; ++i)
        for(j = 0; j < V; ++j)
            fscanf(in, "%d", &feed[i][j]);

    healthy();

    printf("%d ", min_scoop);
    fprintf(out, "%d ", min_scoop);
    for(i = 0; i < min_scoop; ++i)
    {
        printf("%d", min_combi[i]+1);
        fprintf(out, "%d", min_combi[i]+1);
        
        if(i != min_scoop - 1)
        {
            printf(" ");
            fprintf(out, " ");
        }
    }
    printf("\n");
    fprintf(out, "\n");

    return 0;
}
