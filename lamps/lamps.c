/*
ID: southp01
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LAMP 100
#define BUF_SIZE MAX_LAMP + 1
#define MAX_STATE 16

const char* NO_ANS = "IMPOSSIBLE";

struct state
{
        int lamps[BUF_SIZE];
};

struct state all_states[MAX_STATE];
int state_count = 0;

int N;
int C;

struct state begin;
struct state final; /* 0: OFF 1: ON -1: UND */

FILE *in, *out;

enum LAMP_STATE
{
        OFF =  0,
        ON  =  1,
        UND = -1
};

enum BUTTON
{
        BUT_0 = 0,
        BUT_1 = 1,
        BUT_2 = 2,
        BUT_3 = 3,
        BUT_SIZE
};


void print_state(FILE* channel, struct state *st, const char* sep)
{
        int i;

        for(i = 1; i <= N; ++i)
        {
                fprintf(channel, "%d%s", st->lamps[i], sep);
        }
        fprintf(channel, "\n");
}

void toggle(int but_id, struct state *st)
{
        int i = 0;
        int beg = 0, step = 0;

        switch(but_id)
        {
        case BUT_0:
                beg = 1;
                step = 1;

                break;

        case BUT_1:
                beg = 1;
                step = 2;

                break;

        case BUT_2:
                beg = 2;
                step = 2;

                break;

        case BUT_3:
                beg = 1;
                step = 3;

                break;

        default:
                assert(0 && "undefined button id");
                break;
        }
        for(i = beg; i <= N; i += step)
        {
                int old = st->lamps[i];

                st->lamps[i] = 1 - old;
        }
}

int match(struct state *cand, struct state *goal)
{
        int i;

        for(i = 0; i < N; ++i)
        {
                int cv = cand->lamps[i];
                int gv = goal->lamps[i];

                if(gv == UND || cv == gv)
                        continue;
                else
                        return 0;
        }
        return 1;
}

int viable(int count, int goal)
{
        if(count > goal)
        {
                return 0;
        }
        else
        {
                if((goal - count) % 2 == 0)
                        return 1;
                else
                        return 0;
        }
}

void generate_work(struct state cur_state, int bidx, int count)
{
        int i;

        if(bidx > BUT_SIZE)
                return;

        if(match(&cur_state, &final) && viable(count, C))
        {
                printf("matched %d %d: ", bidx, count);
                print_state(stdout, &cur_state, "");

                memcpy(&all_states[state_count], &cur_state, sizeof(all_states[0]));
                ++state_count;
        }

        for(i = bidx; i < BUT_SIZE; ++i)
        {
                toggle(i, &cur_state);
                generate_work(cur_state, i + 1, count + 1);
                toggle(i, &cur_state);
        }
}

void generate()
{
        generate_work(begin, 0, 0);
}

int cmp_state(const void *a, const void *b)
{
        struct state *sa = (struct state*)a;
        struct state *sb = (struct state*)b;
        int i;

        for(i = 0; i < N; ++i)
        {
                int va = sa->lamps[i];
                int vb = sb->lamps[i];

                if(va > vb)
                        return 1;

                else if(vb > va)
                        return -1;
        }

        return 0;
}

int main(int argc, char *argv[])
{
        int i = 0, status;

        int conf[BUF_SIZE];

        if(argc == 2)
                in = fopen(argv[1], "r");
        else
                in = fopen("lamps.in", "r");

        out = fopen("lamps.out", "w");

        fscanf(in, "%d", &N);
        fscanf(in, "%d", &C);

        for(i = 1; i <= MAX_LAMP; ++i)
        {
                begin.lamps[i] = ON;
                final.lamps[i] = UND;
        }

        do
        {
                fscanf(in, "%d", &status);

                if(status != -1)
                        final.lamps[status] = ON;
        }
        while(feof(in) == 0 && status != -1);

        do
        {
                fscanf(in, "%d", &status);

                if(status != -1)
                        final.lamps[status] = OFF;
        }
        while(feof(in) == 0 && status != -1);

        printf("N: %d C: %d\n", N, C);
        printf("final configuration: \n");
        print_state(stdout, &final, ",");

        generate();

        qsort(all_states,
              state_count,
              sizeof(all_states[0]),
              cmp_state);

        printf("Ans: \n");

        if(state_count == 0)
        {
                printf("%s\n", NO_ANS);
                fprintf(out, "%s\n", NO_ANS);
        }
        else
        {
                for(i = 0; i < state_count; ++i)
                {
                        printf("%2d: ", i);
                        print_state(stdout, &all_states[i], "");
                }
                for(i = 0; i < state_count; ++i)
                {
                        print_state(out, &all_states[i], "");
                }
        }

        fclose(in);
        fclose(out);

        return 0;
}

