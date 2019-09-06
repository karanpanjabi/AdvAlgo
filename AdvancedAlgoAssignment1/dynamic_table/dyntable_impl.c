#include "dyntable_impl.h"

#include <stdlib.h>

#define incr_ratio 2.0
#define decr_ratio 0.25

typedef struct
{
    int size;
    int capacity;
    int *arr;
} dyntable;

// Initialize a dynamic table.
void *make_new_dynamic_table(int capacity)
{
    dyntable *table = (dyntable *)malloc(sizeof(dyntable));

    table->size = 0;
    table->capacity = capacity;
    table->arr = (int *)malloc(sizeof(int) * capacity);

    return table;
}

// Inserts element at the end of dynamic table
void push_back(void **table_ptr, int key)
{
    dyntable *table = *table_ptr;

    if (table->size == table->capacity)
    {
        //allocate new block of memory by increasing the capacity

        int *newarr = (int *) malloc(sizeof(int) * table->capacity * incr_ratio);
        table->capacity = table->capacity * incr_ratio;

        for(int i=0; i<table->size; i++)
        {
            newarr[i] = table->arr[i];
        }

        free(table->arr);

        table->arr = newarr;
    }

    table->arr[table->size++] = key;
   
}

// Pops element from the end of dynamic table. Return -1 if empty
int pop_back(void **table_ptr)
{
    
}