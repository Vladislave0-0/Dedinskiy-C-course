#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>

#include "./StackDebug.h"

//=========================================================================================================

const int INITIAL_STK_CAP = 5;

//=========================================================================================================

int stack_ctor(Stack* stk)
{
    if(stk == nullptr)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", STACK_NULLPTR);
        return STACK_NULLPTR;
    }

    stk->capacity = INITIAL_STK_CAP;


    if(open_stack_logs())
    {
        close_stack_logs();
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", STACK_LOGS_NULLPTR);
        return STACK_LOGS_NULLPTR;
    }

    void* stack_ptr = calloc(1, sizeof(elem_t) * stk->capacity + 2 * sizeof(size_t));
    if(stack_ptr == nullptr)
    {
        free(stack_ptr);
        close_stack_logs();
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", STACK_DATA_NULLPTR);
        return STACK_DATA_NULLPTR;
    }

    stk->stack_ptr = stack_ptr;

    stk->left_canary  = (size_t*)stk->stack_ptr;
    stk->data         = (elem_t*)(stk->left_canary + 1);
    stk->right_canary = (size_t*)(stk->data + stk->capacity);

    stk->left_canary[0]  = CANARY;
    stk->right_canary[0] = CANARY;

    fill_with_POISON(stk, 0, stk->capacity);

    stk->data_hash = data_hash(stk);

    stack_print_log(stk);

    return 0;
}

//=========================================================================================================

void stack_push(Stack* stk, elem_t elem)
{
    ASSERT_OK(stk);

    if(stk->size == stk->capacity - 1)
    {
        stack_resize(stk, stk->capacity * RESIZE_FACTOR);
    }
    
    stk->data[stk->size] = elem;

    stk->size++;

    stk->data_hash = data_hash(stk);

    stack_print_log(stk);
}

//=========================================================================================================

void stack_pop(Stack* stk, elem_t* elem)
{
    ASSERT_OK(stk);

    stk->size--;

    *elem = stk->data[stk->size];
    
    stk->data[stk->size] = POISON;

    stk->data_hash = data_hash(stk);

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }

    stk->data_hash = data_hash(stk);
    
    stack_print_log(stk);
}

//=========================================================================================================

void stack_resize(Stack* stk, size_t new_capacity)
{  
    ASSERT_OK(stk);

    size_t old_capacity = stk->capacity;
    stk->capacity = new_capacity;
    
    stk->stack_ptr = realloc(stk->stack_ptr, stk->capacity * sizeof(elem_t) + 2 * sizeof(size_t));

    stk->left_canary  = (size_t*)stk->stack_ptr;
    stk->data         = (elem_t*)(stk->left_canary + 1);
    stk->right_canary = (size_t*)(stk->data + stk->capacity);
    
    stk->left_canary[0]  = CANARY;
    stk->right_canary[0] = CANARY;

    stk->data_hash = data_hash(stk);

    ASSERT_OK(stk);

    fill_with_POISON(stk, old_capacity, stk->capacity); 
}

//=========================================================================================================

void fill_with_POISON(Stack* stk, size_t start, size_t finish)
{
    ASSERT_OK(stk);

    for(size_t i = start; i < finish; i++)
    {
        stk->data[i] = POISON;
    }
}

//=========================================================================================================

void stack_dtor(Stack* stk)
{ 
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

    close_stack_logs();
}
