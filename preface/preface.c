/*
ID: southp01
TASK: preface
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int N;

int roman[] =
{
   [0] = 1,   /* I */
   [1] = 4,   /*IV */
   [2] = 5,   /* V */
   [3] = 9,   /*IX */
   [4] = 10,  /* X */
   [5] = 40,  /*XL */
   [6] = 50,  /* L */
   [7] = 90,  /*XC */
   [8] = 100, /* C */
   [9] = 400, /*CD */
   [10] = 500,/* D */
   [11] = 900,/*CM */
   [12] = 1000/* M */
};

int roman_len = sizeof(roman)/sizeof(int);

struct roman_count
{
    int wc[sizeof(roman)/sizeof(int)];
};

void roman_count_print(struct roman_count* a)
{
    int i;
    for(i = 0; i < roman_len; ++i)
    {
        printf("%d: %d ", roman[i], a->wc[i]);
    }
    printf("\n");
}

struct roman_count convert(int n)
{
    struct roman_count r;
    int i;

    memset(&r, 0, sizeof(r));

    printf("convert: %d\n", n);

    while(n != 0)
    {
        for(i = roman_len - 1; i >= 0; --i)
        {
            if(n >= roman[i])
            {
                r.wc[i] += 1;
                n -= roman[i];
                break;
            }
        }
    }

    roman_count_print(&r);

    return r;
}

void roman_decomp(struct roman_count* a)
{
    if(a->wc[1] != 0) /*IV*/
    {
        int iv = a->wc[1];
        a->wc[1] -= iv;
        a->wc[0] += iv;
        a->wc[2] += iv;
    }
    if(a->wc[3] != 0) /*IX*/
    {
        int ix = a->wc[3];
        a->wc[3] -= ix;
        a->wc[0] += ix;
        a->wc[4] += ix;
    }
    if(a->wc[5] != 0) /*XL*/
    {
        int xl = a->wc[5];
        a->wc[5] -= xl;
        a->wc[4] += xl;
        a->wc[6] += xl;

    }
    if(a->wc[7] != 0) /*XC*/
    {
        int xc = a->wc[7];
        a->wc[7] -= xc;
        a->wc[4] += xc;
        a->wc[8] += xc;
    }
    if(a->wc[9] != 0) /*CD*/
    {
        int cd = a->wc[9];
        a->wc[9] -= cd;
        a->wc[8] += cd;
        a->wc[10] += cd;
    }
    if(a->wc[11] != 0) /*CM*/
    {
        int cm = a->wc[11];
        a->wc[11] -= cm;
        a->wc[8] += cm;
        a->wc[12] += cm;
    }
}

void roman_count_add(struct roman_count* a, struct roman_count* b)
{
    int i;
    for(i = 0; i < roman_len; ++i)
        a->wc[i] += b->wc[i];
}

char letter(int n)
{
    switch(n)
    {
        case 0:
            return 'I';
        case 2:
            return 'V';
        case 4:
            return 'X';
        case 6:
            return 'L';
        case 8:
            return 'C';
        case 10:
            return 'D';
        case 12:
            return 'M';
    }

    return '\0';
}

int main(int argc, char* argv[])
{
    FILE *in, *out = fopen("preface.out", "w");
    int i;
    struct roman_count ans;

    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("preface.in", "r");

    fscanf(in, "%d", &N);
    memset(&ans, 0, sizeof(ans));

    for(i = 1; i <= N; ++i)
    {
        struct roman_count r = convert(i);

        roman_count_add(&ans, &r);
    }

    roman_count_print(&ans);

    roman_decomp(&ans);

    roman_count_print(&ans);

    for(i = 0; i < roman_len; ++i)
    {
        if(ans.wc[i] == 0)
            continue;

        printf("%c %d\n", letter(i), ans.wc[i]);
        fprintf(out, "%c %d\n", letter(i), ans.wc[i]);
    }

    return 0;
}

