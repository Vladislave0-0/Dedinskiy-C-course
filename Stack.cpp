#include "Stack.h"
#include "StackDebug.h"

#include <stdlib.h>
#include <assert.h> 
#include <math.h>

void stack_ctor(Stack* stk, size_t capacity)
{
    assert(stk != nullptr);
    assert(capacity >= 0);

    stk->data = (elem_t*)calloc(capacity, sizeof(elem_t));

    open_stack_logs();

    fill_with_NAN(stk, 0, capacity);

    stk->capacity = capacity;
}

void stack_push(Stack* stk, elem_t elem)
{
    ASSERT_OK(stk);

    if(stk->size == stk->capacity - 1)
    {
        stack_resize(stk, stk->capacity * RESIZE_FACTOR);
    }

    stk->data[stk->size] = elem;

    stk->size++;
}

void stack_pop(Stack* stk, elem_t* result)
{
    ASSERT_OK(stk);

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
    ASSERT_OK(stk);

    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }

    free(stk->data);

    close_stack_logs();
}

void stack_resize(Stack* stk, size_t new_capacity)
{
    ASSERT_OK(stk);

    assert(new_capacity >= 0);

    stk->data = (elem_t*)realloc(stk->data, new_capacity * sizeof(elem_t));

    fill_with_NAN(stk, stk->capacity, new_capacity);

    stk->capacity = new_capacity;
}

void fill_with_NAN(Stack* stk, size_t start, size_t finish)
{
    for(size_t i = start; i <= finish; i++)
    {
        stk->data[i] = NAN;
    }
}

void stack_print(Stack* stk)
{

    printf("{\n");

    printf("size     = %lu\n", stk->size);

    printf("capacity = %lu\n", stk->capacity);

    printf("data     = [%p]\n", stk->data);

    printf("\t{\n");

    for(size_t i = 0; i <= stk->capacity; i++)
    {
        if(!isnan(stk->data[i]))
        {
            printf("\t*[%lu] = %g\n", i, stk->data[i]);
        }

        else 
        {
            printf("\t [%lu] = NAN\n", i);
        }
    }

    printf("\t}\n");

    printf("}\n\n");
}