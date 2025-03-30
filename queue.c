#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

/*bool comp_array(uint8_t arr1[4][4], uint8_t arr2[4][4])
{
    for (uint8_t i = 0; i < 4; i++) 
    {
        for (uint8_t j = 0; j < 4; j++) 
        {
            if (arr1[i][j] != arr2[i][j])
            {
                return false;
            }
        }
    }   
    return true;
}*/

bool check(uint64_t* arr, int pos, uint64_t cur)
{
    for (int i = 0; i < pos; i++)
    {
        if (arr[i] == cur)
        {
            return true;
        }
    }
    return false;
}

void enqueue(struct queue *q, struct game_state state) 
{
    insert_at_head(&(q->data), serialize(state));
}

struct game_state dequeue(struct queue *q) 
{
    size_t state = remove_from_tail(&(q->data));
    return (deserialize(state)); 
}

int number_of_moves(struct game_state start) 
{ 
    struct queue q;
    q.data.head = NULL;
    enqueue(&q, start);
    //to compare against
    //
    /*struct game_state end;
    end.num_steps = 0;
    int value=0;
    for (uint8_t i = 0; i < 4; i++) 
    {
        for (uint8_t j = 0; j < 4; j++) 
        {
            if (i == 3 && j == 3)
            {
                break;
            }
            else
            {
                value++;
            }
            end.tiles[i][j] = value;
        }
    }
    end.empty_row = 3;
    end.empty_col = 3;*/
    //
    struct game_state cur = start;
    struct game_state test = cur;
    uint64_t *checked = calloc(1000000, sizeof(uint64_t));
    int pos = 0;
    checked[pos] = serialize(cur);
    pos++;


    while(serialize(test) != 81985526993846272)// cur.empty_col != end.empty_col || cur.empty_row != end.empty_row)// ||  !comp_array(cur.tiles, end.tiles))
    {

        struct game_state up = cur;
        struct game_state down = cur;
        struct game_state left = cur;
        struct game_state right = cur;
        struct game_state temp;
        move_up(&up);
        temp = up;
        temp.num_steps = 0;
        if (!check(checked, pos, serialize(temp)))
        {
            checked[pos] = serialize(temp);
            pos++;
            enqueue(&q, up);
        }
        move_down(&down);
        temp = down;
        temp.num_steps = 0;
        if (!check(checked, pos, serialize(temp)))
        {
            checked[pos] = serialize(temp);
            pos++;
            enqueue(&q, down);
        }
        move_left(&left);
        temp = left;
        temp.num_steps = 0;
        if (!check(checked, pos, serialize(temp)))
        {
            checked[pos] = serialize(temp);
            pos++;
            enqueue(&q, left);
        }
        move_right(&right);
        temp = right;
        temp.num_steps = 0;
        if (!check(checked, pos, serialize(temp)))
        {
            checked[pos] = serialize(temp);
            pos++;
            enqueue(&q, right);
        }
        cur = dequeue(&q);
        test = cur;
        test.num_steps = 0;
    }
    free_list(q.data);
    free(checked);
    return cur.num_steps;
}
