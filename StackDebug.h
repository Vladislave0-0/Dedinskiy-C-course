#ifndef STACK_DEBUG_H
#define STACK_DEBUG_H

//=========================================================================================================

#include "Stack.h"

//=========================================================================================================

#define ASSERT_OK(stk)                                   \
    do                                                   \
    {                                                    \
        if(stack_verify(stk) != 0)                       \
        {                                                \
            STACK_DUMP(stk);                             \
            close_stack_logs();                          \
            assert_dtor(stk);                            \
        }                                                \
    } while(0)                                           \

//=========================================================================================================

enum StackErrors
{
    ERROR_DATA_NULLPTR              = 1 << 0,     // stk->data == nullptr
    ERROR_STACK_PTR                 = 1 << 1,     // stk->stack_ptr == nullptr
    ERROR_SIZE_BELOW_NULL           = 1 << 2,     // stk->size < 0
    ERROR_SIZE_BIGGER_THAN_CAPACITY = 1 << 3,     // stk->size > stk->capacity
    ERROR_LEFT_CANARY_DEAD          = 1 << 4,     // stk->left_canary[0] != CANARY
    ERROR_LEFT_CANARY_NULLPTR       = 1 << 5,     // stk->left_canary == nullptr
    ERROR_RIGHT_CANARY_DEAD         = 1 << 6,     // stk->right_canary[0] != CANARY
    ERROR_RIGHT_CANARY_NULLPTR      = 1 << 7,     // stk->right_canary == nullptr
};

//=========================================================================================================

void stack_dump(Stack* stk, const char* file_name, size_t line, const char* function_name);

int stack_verify(Stack* stk);

void stack_error_decoder(Stack* stk);

void assert_dtor(Stack* stk);

void open_stack_logs();

void stack_print_log(Stack* stk);

void close_stack_logs();

//=========================================================================================================

#endif