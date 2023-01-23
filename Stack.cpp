#include "Stack.h"
#include <stdlib.h>
#include <assert.h> 

void stack_ctor(Stack* stk, size_t capacity)
{
    assert(stk != nullptr);
    assert(capacity >= 0);

    stk->data = (elem_t*)calloc(capacity, sizeof(elem_t));

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
        //realloc
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
    stk->data[stk->size] = 0;

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        //resize down x2
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