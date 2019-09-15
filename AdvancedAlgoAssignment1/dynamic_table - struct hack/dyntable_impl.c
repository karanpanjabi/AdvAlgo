#include "dyntable_impl.h"

#include <stdlib.h>

#include <stdio.h>

#define incr_ratio 2.0
#define decr_ratio 0.5

#define load_factor_upper 1.0
#define load_factor_lower 0.05

#define DEBUG 0

static int copy = 0;

typedef struct
{
    int num;
    int size;
    int arr[0];

} dyntable;

// Initialize a dynamic table.
void *make_new_dynamic_table(int capacity)
{

    dyntable *table = (dyntable *)malloc(sizeof(dyntable) + sizeof(int) * capacity);
    table->num = 0;
    table->size = capacity;

    return (void *)table;
}

// Inserts element at the end of dynamic table
void push_back(void **table_ptr, int key)
{
    dyntable *table = *table_ptr;
    if (table->size == 0)
    {
        dyntable *newtable = (dyntable *)malloc(sizeof(dyntable) + sizeof(int));
        newtable->size = 1;
        newtable->num = 0;

        free(table);
        *table_ptr = newtable;
        table = newtable;
    }
    else if ((float)table->num / table->size >= load_factor_upper)
    {
        //allocate new block of memory by increasing the size

        int newsize = (int)(table->size * incr_ratio);
        dyntable *newtable = (dyntable *)malloc(sizeof(dyntable) + sizeof(int) * newsize);

        newtable->size = newsize;
        newtable->num = table->num;

        for (int i = 0; i < table->num; i++)
        {
            newtable->arr[i] = table->arr[i];
        }
        copy++;

        free(table);
        *table_ptr = newtable;
        table = newtable;
    }

    table->arr[table->num++] = key;


#if DEBUG
    printf("Push ");
    displayStats(table_ptr);
#endif
}

// Pops element from the end of dynamic table. Return -1 if empty
int pop_back(void **table_ptr)
{
    dyntable *table = *table_ptr;
    int popped = -1;
    if (table->num == 0)
    {
        return -1;
    }
    popped = table->arr[table->num - 1];
    table->num--;

    if ((float)table->num / table->size <= load_factor_lower)
    {
        //allocate a new block of memory and decrease size

        int newsize = (int)(table->size * decr_ratio);
        dyntable *newtable = (dyntable *)malloc(sizeof(dyntable) + sizeof(int) * newsize);

        newtable->size = newsize;
        newtable->num = table->num;

        for (int i = 0; i < table->num; i++)
        {
            newtable->arr[i] = table->arr[i];
        }
        copy++;

        free(table);

        *table_ptr = newtable;
        table = newtable;
    }

#if DEBUG
    printf("Pop ");
    displayStats(table_ptr);
#endif

    return popped;
}

#if DEBUG
void displayStats(void **table_ptr)
{
    dyntable *table = *table_ptr;

    printf("%d %d\n", table->num, table->size);
    for (int i = 0; i < table->num; i++)
    {
        printf("%d ", table->arr[i]);
    }
    printf("\n\n");
}
#endif

void printCopy(void **table_ptr)
{
    printf("Copy called: %d, final size: %d\n", copy, ((dyntable* ) *table_ptr)->size);
}