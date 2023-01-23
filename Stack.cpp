#include "Stack.h"
#include <stdlib.h>
#include <assert.h> 
#include <math.h>


static FILE* LOG_FILE = nullptr;

#define PRINT_LOG(...) fprintf(LOG_FILE, __VA_ARGS__)

void stack_ctor(Stack* stk, size_t capacity)
{
    assert(stk != nullptr);
    assert(capacity >= 0);

    stk->data = (elem_t*)calloc(capacity, sizeof(elem_t));

    fill_with_NAN(stk, 0, capacity);

    stk->capacity = capacity;
}

void stack_push(Stack* stk, elem_t elem)
{
    assert(stk != nullptr);
    assert(stk->data != nullptr);
    assert(stk->size >= 0);
    assert(stk->size <= stk->capacity);

    if(stk->size <= stk->capacity - 1)
    {
        stk->data[stk->size] = elem;

        stk->size++;
    }

    else
    {
        stack_resize(stk, stk->capacity * RESIZE_FACTOR);
    }
}

void stack_pop(Stack* stk, elem_t* result)
{
    assert(stk != nullptr);
    assert(stk->data != nullptr);
    assert(stk->size >= 0);
    assert(stk->size <= stk->capacity);
    assert(result != nullptr);

    stk->size--;

    *result = stk->data[stk->size];
    stk->data[stk->size] = NAN;

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }
}

void stack_dtor(Stack* stk)
{    
    assert(stk != nullptr);

    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }

    free(stk->data);
}

void stack_print(Stack* stk)
{
    PRINT_LOG("{\n");

    PRINT_LOG("size     = %lu\n", stk->size);

    PRINT_LOG("capacity = %lu\n", stk->capacity);

    PRINT_LOG("data     = [%p]\n", stk->data);

    PRINT_LOG("\t{\n");

    for(size_t i = 0; i < stk->capacity; i++)
    {
        if(!isnan(stk->data[i]))
        {
            PRINT_LOG("\t*[%lu] = %g\n", i, stk->data[i]);
        }

        else 
        {
            PRINT_LOG("\t [%lu] = NAN\n", i);
        }
    }

    PRINT_LOG("\t}\n");

    PRINT_LOG("}\n\n");
}

void open_stack_logs()
{
    LOG_FILE = fopen("./Logs/stack_log.txt", "w");
}

void close_stack_logs()
{
    fclose(LOG_FILE);
}

void stack_resize(Stack* stk, size_t new_capacity)
{
    assert(new_capacity >= 0);

    stk->data = (elem_t*)realloc(stk->data, new_capacity * sizeof(elem_t));

    fill_with_NAN(stk, stk->capacity, new_capacity);

    stk->capacity = new_capacity;
}

void fill_with_NAN(Stack* stk, size_t start, size_t finish)
{
    for(size_t i = start; i < finish; i++)
    {
        stk->data[i] = NAN;
    }
}