#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>

#include "StackDebug.h"

//=========================================================================================================

Stack* stack_ctor(size_t capacity)
{
    assert(capacity >= 0);

    open_stack_logs();

    Stack* stk = (Stack*)calloc(1, sizeof(Stack));
    assert(stk != nullptr);    

    stk->data = (elem_t*)calloc(capacity, sizeof(elem_t));
    assert(stk->data != nullptr);    

    stk->capacity = capacity;

    fill_with_NAN(stk, 0, capacity);

    return stk;
}

//=========================================================================================================

void stack_push(Stack* stk, elem_t elem)
{
    assert(stk != nullptr); 
    assert(stk->data != nullptr);   
    ASSERT_OK(stk);

    if(stk->size == stk->capacity - 1)
    {
        stack_resize(stk, stk->capacity * RESIZE_FACTOR);
    }

    stk->data[stk->size] = elem;

    stk->size++;
}

//=========================================================================================================

void stack_pop(Stack* stk, elem_t* result)
{
    assert(stk != nullptr);
    assert(stk->data != nullptr);   
    assert(result != nullptr);
    ASSERT_OK(stk);

    stk->size--;

    *result = stk->data[stk->size];
    
    stk->data[stk->size] = NAN;

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }
}

//=========================================================================================================

void stack_dtor(Stack* stk)
{    
    assert(stk != nullptr);
    assert(stk->data != nullptr);    
    ASSERT_OK(stk);

    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }

    free(stk->data);

    free(stk);

    close_stack_logs();
}

//=========================================================================================================

void stack_resize(Stack* stk, size_t new_capacity)
{
    assert(stk != nullptr);
    assert(stk->data != nullptr); 
    assert(new_capacity >= 0);   
    ASSERT_OK(stk);

    stk->data = (elem_t*)realloc(stk->data, new_capacity * sizeof(elem_t));

    fill_with_NAN(stk, stk->capacity, new_capacity);

    stk->capacity = new_capacity;
}

//=========================================================================================================

void fill_with_NAN(Stack* stk, size_t start, size_t finish)
{
    assert(stk != nullptr);
    assert(stk->data != nullptr); 

    for(size_t i = start; i <= finish; i++)
    {
        stk->data[i] = NAN;
    }
}
