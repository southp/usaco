/*
ID: southp01
LANG: C
TASK: lamps
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LAMP 100
#define BUF_SIZE MAX_LAMP + 1
#define MAX_STATE 16

struct state
{
        int lamps[BUF_SIZE];
};

struct state all_states[MAX_STATE];
int state_count = 0;

int N;
int C;
int begin[BUF_SIZE];
int final[BUF_SIZE]; /* 0: OFF 1: ON -1: UND */

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

void generate_work(int button[], int but_id, int count)
{
}

void generate()
{
        static int button[BUT_SIZE];

        memset(button, 0, sizeof(button));

        generate_work(button, BUT_0, 0);
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
                begin[i] = ON;
                final[i] = UND;
        }

        do
        {
                fscanf(in, "%d", &status);

                if(status != -1)
                        final[status] = ON;
        }
        while(feof(in) != 0 && status != -1);

        do
        {
                int status = 0;

                fscanf(in, "%d", &status);

                if(status != -1)
                        final[status] = OFF;
        }
        while(feof(in) != 0 && status != -1);

        printf("N: %d C: %d\n", N, C);
        printf("final configuration: \n");
        for(i = 1; i < N; ++i)
                printf("%d ", final[i]);
        printf("\n");

        generate();

        fclose(in);
        fclose(out);

        return 0;
}

