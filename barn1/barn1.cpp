/*
ID: southp01
TASK: barn1
LANG: C++
*/

#include <stdio.h>
#include <string.h>
#include <algorithm>

int M,S,C;

bool stalls[200 + 1];
int occupied[200];
int main(int argc, char* argv[])
{
    FILE *in,*out = fopen("barn1.out","w");
    if(argc == 2)
    {
        in = fopen(argv[1],"r");
    }
    else
    {
        in = fopen("barn1.in","r");
    }
    memset(occupied,0,sizeof(occupied));
    fscanf(in,"%d %d %d",&M,&S,&C);
    for(int i = 0; i < C; ++i)
    {
        fscanf(in,"%d",&occupied[i]);
    }
    std::sort(occupied,occupied+C);
    int beg = occupied[0],end = occupied[C-1];
    for(int i = beg; i <= end; ++i)
    {
        stalls[i] = 1;
    }

    int num_board = M;
    while(--num_board) //on purpose
    {
        int max_span = -1, mp = 0, mc = 0;
        for(int prev = 0,cur = 1; cur < C; ++prev,++cur)
        {
            int oc = occupied[cur] - 1, 
                op = occupied[prev] + 1;
            if(oc >= op && stalls[oc] && stalls[op])
            {
                int span = oc - op;
                if(span > max_span)
                {
                    max_span = span;
                    mp = op;
                    mc = oc;
                }
            }
        }
        printf("choosed: %d %d\n",mp,mc);
        for(int i = mp; i <= mc; ++i)
        {
            stalls[i] = false;
        }
    }

    int total = 0;
    for(int i = 1; i <= S; ++i)
    {
        if(stalls[i])
        {
            ++total;
            printf("%d ",i);
        }
    }
    printf("\n%d\n",total);
    fprintf(out,"%d\n",total);
    fscanf(in,"%d %d %d",&M,&S,&C);
    fclose(in);
    return 0;
}

