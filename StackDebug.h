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
        }                                                \
    } while(0)                                           \

//=========================================================================================================

enum StackErrors
{
    STACK_ERROR_DATA_NULL                 = 1 << 0,     // 2^1 or 001
    STACK_ERROR_SIZE_BELOW_NULL           = 1 << 1,     // 2^2 or 010
    STACK_ERROR_SIZE_BIGGER_THAN_CAPACITY = 1 << 2,     // 2^3 or 100
};

//=========================================================================================================

void open_stack_logs();

void stack_print_log(Stack* stk);

void close_stack_logs();

int stack_verify(Stack* stk);

void stack_error_decoder(Stack* stk);

void stack_dump(Stack* stk, const char* file_name, size_t line, const char* function_name);

//=========================================================================================================

#endif