/*
ID: southp01
TASK: ride
LANG: C++
*/

#include <stdio.h>
#include <string.h>

int convert(char* str)
{
    int pro = 1;
    int len = strlen(str);
    for(int i = 0; i < len; ++i)
    {
        pro *= static_cast<int>(str[i] - 'A') + 1;
    }
    return pro % 47;
}

int main(int argc,char* argv[])
{
    FILE *in,*out;
    char group[8],ufo[8];
    if(argc == 2)
    {
        in = fopen(argv[1],"r");
    }
    else
    {
        in = fopen("ride.in","r");
    }
    fscanf(in,"%s",group);
    fscanf(in,"%s",ufo);
    fclose(in);
    
    out = fopen("ride.out","w");
    if(convert(group) == convert(ufo))
    {
        fprintf(out,"GO\n");
    }
    else
    {
        fprintf(out,"STAY\n");
    }
    fclose(out);
    return 0;
}
