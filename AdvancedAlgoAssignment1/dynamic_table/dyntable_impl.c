#include "dyntable_impl.h"

#include <stdlib.h>

#include <stdio.h>

#define incr_ratio 2.0
#define decr_ratio 0.5

#define load_factor_upper 1.0
#define load_factor_lower 0.25

#define STRUCT_HACK 1

#define DEBUG 1

typedef struct
{
    int num;
    int size;

#if STRUCT_HACK
    int arr[0];

#else
    int *arr;

#endif
} dyntable;

// Initialize a dynamic table.
void *make_new_dynamic_table(int capacity)
{

#if STRUCT_HACK
    dyntable *table = (dyntable *)malloc(sizeof(dyntable) + sizeof(int) * capacity);

#else
    dyntable *table = (dyntable *)malloc(sizeof(dyntable));

#endif

    table->num = 0;
    table->size = capacity;

#if !STRUCT_HACK
    table->arr = (int *)malloc(sizeof(int) * capacity);

#endif

    return (void *)table;
}

// Inserts element at the end of dynamic table
void push_back(void **table_ptr, int key)
{

#if !STRUCT_HACK

    dyntable *table = *table_ptr;
    if (table->size == 0)
    {
        table->arr = (int *)malloc(sizeof(int));
        table->size++;
    }
    else if ((float)table->num / table->size >= load_factor_upper)
    {
        //allocate new block of memory by increasing the size

        table->size = (int)(table->size * incr_ratio);
        int *newarr = (int *)malloc(sizeof(int) * table->size);

        for (int i = 0; i < table->num; i++)
        {
            newarr[i] = table->arr[i];
        }

        free(table->arr);

        table->arr = newarr;
    }

    table->arr[table->num++] = key;

#else
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

        free(table);
        *table_ptr = newtable;
        table = newtable;
    }

    table->arr[table->num++] = key;

#endif

#if DEBUG
    printf("Push ");
    displayStats(table_ptr);
#endif
}

// Pops element from the end of dynamic table. Return -1 if empty
int pop_back(void **table_ptr)
{

#if !STRUCT_HACK
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

        table->size = (int)(table->size * decr_ratio);
        int *newarr = (int *)malloc(sizeof(int) * table->size);

        for (int i = 0; i < table->num; i++)
        {
            newarr[i] = table->arr[i];
        }

        free(table->arr);

        table->arr = newarr;
    }

#else
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

        free(table);

        *table_ptr = newtable;
        table = newtable;
    }

#endif


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