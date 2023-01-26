#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>

#include "StackDebug.h"

//=========================================================================================================

Stack* stack_ctor()
{
    size_t capacity = 0;
    printf("Please, enter the capacity of stack: ");
    scanf("%lu", &capacity);

    open_stack_logs();

    Stack* stk = (Stack*)calloc(1, sizeof(Stack));
    assert(stk != nullptr);

    stk->capacity = capacity;   

    stk->stack_ptr = calloc(1, sizeof(elem_t) * stk->capacity + 2 * sizeof(size_t));
    assert(stk->stack_ptr != nullptr);

    stk->left_canary  = (size_t*)stk->stack_ptr;
    stk->data         = (elem_t*)(stk->left_canary + 1);
    stk->right_canary = (size_t*)(stk->data + stk->capacity);

    stk->left_canary[0]  = CANARY;
    stk->right_canary[0] = CANARY;

    fill_with_NAN(stk, 0, stk->capacity);

    stk->data_hash = stack_data_hash(stk);

    return stk;
}

//=========================================================================================================

void stack_push(Stack* stk, elem_t elem)
{
    assert(stk != nullptr);
    ASSERT_OK(stk);

    if(stk->size == stk->capacity - 1)
    {
        stack_resize(stk, stk->capacity * RESIZE_FACTOR);
    }

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }

    stk->data[stk->size] = elem;

    stk->size++;

    stk->data_hash = stack_data_hash(stk);
}

//=========================================================================================================

void stack_pop(Stack* stk)
{
    assert(stk != nullptr);
    ASSERT_OK(stk);

    stk->size--;
    
    stk->data[stk->size] = NAN;

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }

    stk->data_hash = stack_data_hash(stk);
}

//=========================================================================================================

void stack_resize(Stack* stk, size_t new_capacity)
{
    assert(stk != nullptr);
    assert(new_capacity > 0);   
    ASSERT_OK(stk);

    size_t old_capacity = stk->capacity;
    stk->capacity = new_capacity;
    
    stk->stack_ptr = realloc(stk->stack_ptr, stk->capacity * sizeof(elem_t) + 2 * sizeof(size_t));

    stk->left_canary  = (size_t*)stk->stack_ptr;
    stk->data         = (elem_t*)(stk->left_canary + 1);
    stk->right_canary = (size_t*)(stk->data + stk->capacity);
    
    stk->left_canary[0]  = CANARY;
    stk->right_canary[0] = CANARY;
    ASSERT_OK(stk);

    fill_with_NAN(stk, old_capacity, stk->capacity); 
}

//=========================================================================================================

void fill_with_NAN(Stack* stk, size_t start, size_t finish)
{
    assert(stk != nullptr); 
    ASSERT_OK(stk);

    for(size_t i = start; i < finish; i++)
    {
        stk->data[i] = NAN;
    }
}

//=========================================================================================================

void stack_dtor(Stack* stk)
{    
    assert(stk != nullptr);  
    ASSERT_OK(stk);

    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }

    stk->capacity     = 0;
    stk->size         = 0;
    stk->error_code   = 0;
    stk->data_hash    = 0;
    stk->data         = nullptr;
    stk->left_canary  = nullptr;
    stk->right_canary = nullptr;

    free(stk->stack_ptr);
    stk->stack_ptr = nullptr;

    free(stk);
    stk = nullptr;

    close_stack_logs();
}
