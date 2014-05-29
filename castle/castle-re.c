/*
ID: southp01
LANG: C
TASK: castle 
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MAX_DIM  50
#define MAX_ROOM MAX_DIM*MAX_DIM + 1
#define WEST     1
#define NORTH    2
#define EAST     4
#define SOUTH    8

/*          Basic building block          */
struct room_node
{
    int  id;
    int  r, c;
    char wall;
    struct room_node* next;
};

struct room_list
{
    struct room_node* begin;
    struct room_node* end;
};

void room_list_append(struct room_list* list, int r, int c, char wall)
{
    struct room_node* new_end = (struct room_node*)malloc(sizeof(struct room_node));
    new_end->r = r;
    new_end->c = c;
    new_end->wall = wall;
    new_end->next = NULL;

    if(list->begin == NULL)
    {
        list->begin = new_end;
        list->end = new_end;
    }
    else
    {
        list->end->next = new_end;
        list->end = new_end;
    }
}

void room_list_append_node(struct room_list* list, struct room_node* node)
{
    if(list->begin == NULL)
    {
        list->begin = node;
        list->end = node;
    }
    else
    {
        list->end->next = node;
        list->end = node;
    }
}

/*   End of basic building block          */

int mods[MAX_DIM][MAX_DIM]; /* rows * cols */
int fill[MAX_DIM][MAX_DIM];
int room_size[MAX_ROOM];
int M, N;
int num_room  = 0;
int room_id   = 1;
int max_size  = 0;
int cur_size  = 0;

int  max_merge = 0;

struct room_node merge_room;
struct room_list neighbor_room_buf[MAX_ROOM];
struct room_list room_graph[MAX_ROOM];

void mark_neighbor(int r, int c, char wall)
{
    if(r >= 0 && r < N && c >=0 && c < M)
    {
        room_list_append(&neighbor_room_buf[room_id], r, c, wall);
    }
}

void ff(int r, int c)
{
    if(r >= 0 && r < N && c >=0 && c < M)
    {
        int mod = mods[r][c];

        if(fill[r][c] != 0)
            return;

        fill[r][c] = room_id;
        ++cur_size;

        if(!(mod & WEST))
            ff(r, c-1);
        else
            mark_neighbor(r, c-1, 'E');

        if(!(mod & NORTH))
            ff(r-1, c);

        if(!(mod & EAST))
            ff(r, c+1);
        
        if(!(mod & SOUTH))
            ff(r+1, c);
        else
            mark_neighbor(r+1, c, 'N');
    }
}

void count_room()
{
    int r, c;

    for(r = 0; r < N; ++r)
        for(c = 0; c < M; ++c)
        {
            if(fill[r][c] == 0)
            {
                cur_size = 0;

                ff(r, c);

                room_size[room_id] = cur_size;
                ++num_room;
                ++room_id;

                max_size = cur_size > max_size? cur_size : max_size;
            }
        }
}

int room_is_greater(struct room_node* a, struct room_node* b)
{
    if(a->c < b->c)
    {
        return 1;
    }
    else if(a->c == b->c)
    {
        if(a->r > b->r)
        {
            return 1;
        }
        else if(a->r == b->r)
        {
            if(a->wall == 'N')
            {
                return 1;
            }
        }
    }
    return 0;
}

void dump_neighbor()
{
    printf("neighbor dump: \n");
    int i;
    for(i = 1; i <= num_room; ++i)
    {
        struct room_node* cur = neighbor_room_buf[i].begin;

        printf("%d : ", i);
        while(cur != NULL)
        {
            printf("(%d,%d,%c) ", cur->r + 1, cur->c + 1, cur->wall);
            cur = cur->next;
        }
        printf("\n");
    }
}

void link_room()
{
    dump_neighbor();
    int i;

    for(i = 1; i <= num_room; ++i)
    {
        struct room_list* myroom = &room_graph[i];
        struct room_node* cur = neighbor_room_buf[i].begin;
        struct room_node* record[MAX_ROOM];

        memset(record, 0, sizeof(record));
        record[i] = (struct room_node*)1; /* just a record */
        while(cur != NULL)
        {
            struct room_node* new_end = (struct room_node*)malloc(sizeof(struct room_node));
            int id = fill[cur->r][cur->c];
            new_end->id   = id;
            new_end->r    = cur->r;
            new_end->c    = cur->c;
            new_end->wall = cur->wall;
            new_end->next = NULL;

            if(!record[id])
            {
                room_list_append_node(myroom, new_end);
                record[id] = new_end;
            }
            else
            {
                struct room_node* node = record[id];

                if((int)node == 1)
                {
                    cur = cur->next;
                    continue;
                }

                if(room_is_greater(cur, node))
                {
                    node->r = cur->r;
                    node->c = cur->c;
                    node->wall = cur->wall;
                }

            }

            cur = cur->next;
        }
    }
}

void dump_room()
{
    printf("Room dump: \n");
    int i;
    for(i = 1; i <= num_room; ++i)
    {
        struct room_node* cur = room_graph[i].begin;

        printf("%d: ", i);
        while(cur != NULL)
        {
            printf("%d ", cur->id);
            cur = cur->next;
        }
        printf("\n");
    }
}

void merge()
{
    dump_room();
    int i;

    for(i = 1; i <= num_room; ++i)
    {
        struct room_node* target = room_graph[i].begin;
        int my_size = room_size[i];

        while(target != NULL)
        {
            int target_merge = room_size[target->id] + my_size;
            
            if(target_merge > max_merge)
            {
                printf("Merge: %d %d\n", i, target->id);

                max_merge = target_merge;
                memcpy(&merge_room, target, sizeof(struct room_node));
            }
            else if(target_merge == max_merge)
            {
                if(room_is_greater(target, &merge_room))
                {
                    memcpy(&merge_room, target, sizeof(struct room_node));
                }
            }

            target = target->next;
        }
    }
}

void init()
{
    memset(mods, 0, sizeof(mods));
    memset(fill, 0, sizeof(fill));
    memset(room_graph, 0, sizeof(room_graph));
    memset(room_size, 0, sizeof(room_size));
    memset(neighbor_room_buf, 0, sizeof(neighbor_room_buf));
}

int main(int argc, char* argv[])
{
    FILE* in = NULL;
    FILE* out = fopen("castle.out", "w");
    int i, j;
    if(argc == 2)
        in = fopen(argv[1], "r");
    else
        in = fopen("castle.in", "r");

    fscanf(in, "%d %d", &M, &N);

    init();

    for(i = 0; i < N; ++i)
        for(j = 0; j < M; ++j)
        {
            fscanf(in, "%d", &mods[i][j]);
        }

    printf("M: %d, N: %d\n", M, N);
    for(i = 0; i < N; ++i)
    {
        for(j = 0; j < M; ++j)
        {
            printf("%d ", mods[i][j]);
        }
        printf("\n");
    }
    
    count_room();
    link_room();
    merge();

    printf("\n");
    printf("%d\n%d\n%d\n%d %d %c\n", num_room
                         , max_size
                         , max_merge
                         , merge_room.r + 1, merge_room.c + 1, merge_room.wall);

    fprintf(out, "%d\n%d\n%d\n%d %d %c\n", num_room
                                         , max_size
                                         , max_merge
                                         , merge_room.r + 1, merge_room.c + 1, merge_room.wall);

    fclose(out);

    return 0;
}
