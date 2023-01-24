#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>

#include "StackDebug.h"

FILE* LOG_FILE = nullptr;

//=========================================================================================================

void stack_dump(Stack* stk, const char* file_name, size_t line, const char* function_name)
{
    PRINT_LOG("in %s at %s(%lu):\n", function_name, file_name, line);

    PRINT_LOG("Stack[%p]", stk->data);

    stack_error_decoder(stk);

    stack_print_log(stk);
}

//=========================================================================================================

int stack_verify(Stack* stk)
{
    stk->error_code = (stk->data == nullptr) * STACK_ERROR_DATA_NULL   +
    (stk->size < 0) * STACK_ERROR_SIZE_BELOW_NULL                      + 
    (stk->size > stk->capacity) * STACK_ERROR_SIZE_BIGGER_THAN_CAPACITY;

    return stk->error_code;
}

//=========================================================================================================

void stack_error_decoder(Stack* stk)
{
    if(stk->error_code == 0)
    {
        PRINT_LOG("(OK)\n");
    }

    else
    {
        if(stk->error_code & STACK_ERROR_DATA_NULL)
        {
            PRINT_LOG("STACK_ERROR_DATA_NULL\n");
        }

        if(stk->error_code & STACK_ERROR_SIZE_BELOW_NULL)
        {
            PRINT_LOG("STACK_ERROR_SIZE_BELOW_NULL\n");
        }

        if(stk->error_code & STACK_ERROR_SIZE_BIGGER_THAN_CAPACITY)
        {
            PRINT_LOG("STACK_ERROR_SIZE_BIGGER_THAN_CAPACITY\n");
        }
    }
}

//=========================================================================================================

void open_stack_logs()
{
    LOG_FILE = fopen("./Logs/stack_log.txt", "w");
}

//=========================================================================================================

void stack_print_log(Stack* stk)
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

//=========================================================================================================

void close_stack_logs()
{
    fclose(LOG_FILE);
}
