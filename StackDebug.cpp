#include <stdio.h>
#include <stdlib.h>
#include <assert.h> 
#include <math.h>

#include "StackDebug.h"

//=========================================================================================================

FILE* LOG_FILE = nullptr;

//=========================================================================================================

void stack_dump(Stack* stk, const char* file_name, size_t line, const char* function_name)
{
    assert(stk != nullptr);

    PRINT_LOG("in %s at %s(%lu):\n", function_name, file_name, line);

    PRINT_LOG("Stack[%p]", stk->data);

    stack_error_decoder(stk);
}

//=========================================================================================================

int stack_verify(Stack* stk)
{
    assert(stk != nullptr);

    stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR   +
    (stk->stack_ptr == nullptr) * ERROR_STACK_PTR                   +
    (stk->size < 0) * ERROR_SIZE_BELOW_NULL                         + 
    (stk->size > stk->capacity) * ERROR_SIZE_BIGGER_THAN_CAPACITY   +
    (stk->left_canary[0] != CANARY) * ERROR_LEFT_CANARY_DEAD        +
    (stk->left_canary == nullptr) * ERROR_LEFT_CANARY_NULLPTR       +
    (stk->right_canary[0] != CANARY) * ERROR_RIGHT_CANARY_DEAD      +
    (stk->right_canary == nullptr) * ERROR_RIGHT_CANARY_NULLPTR;

    return stk->error_code;
}

//=========================================================================================================

void stack_error_decoder(Stack* stk)
{
    assert(stk != nullptr);

    if(stk->error_code == 0)
    {
        PRINT_LOG(" -> (OK)\n");
    }

    else
    {
        if(stk->error_code & ERROR_DATA_NULLPTR)
        {
            PRINT_LOG("STACK_ERROR_DATA_NULL.\n");
        }

        if(stk->error_code & ERROR_STACK_PTR)
        {
            PRINT_LOG("ERROR_STACK_PTR.\n");
        }

        if(stk->error_code & ERROR_SIZE_BELOW_NULL)
        {
            PRINT_LOG("STACK_ERROR_SIZE_BELOW_NULL.\n");
        }

        if(stk->error_code & ERROR_SIZE_BIGGER_THAN_CAPACITY)
        {
            PRINT_LOG("STACK_ERROR_SIZE_BIGGER_THAN_CAPACITY.\n");
        }

        if(stk->error_code & ERROR_LEFT_CANARY_DEAD)
        {
            PRINT_LOG("ERROR_LEFT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_LEFT_CANARY_NULLPTR)
        {
            PRINT_LOG("ERROR_LEFT_CANARY_NULLPTR.\n");
        }   

        if(stk->error_code & ERROR_RIGHT_CANARY_DEAD)
        {
            PRINT_LOG("ERROR_RIGHT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_RIGHT_CANARY_NULLPTR)
        {
            PRINT_LOG("ERROR_RIGHT_CANARY_NULLPTR.\n");
        }                     
    }

    printf("\n\n");
}

//=========================================================================================================э

void assert_dtor(Stack* stk)
{
    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }


    stk->capacity     = 0;
    stk->size         = 0;
    stk->error_code   = 0;
    stk->data         = nullptr;
    stk->left_canary  = nullptr;
    stk->right_canary = nullptr;


    free(stk->stack_ptr);
    stk->stack_ptr = nullptr;

    free(stk);
    stk = nullptr;  
}

//=========================================================================================================

void open_stack_logs()
{
    LOG_FILE = fopen("./Logs/stack_log.txt", "w");
}

//=========================================================================================================

void stack_print_log(Stack* stk)
{
    assert(stk != nullptr);

    PRINT_LOG("{\n");

    PRINT_LOG("size     = %lu\n", stk->size);

    PRINT_LOG("capacity = %lu\n", stk->capacity);

    PRINT_LOG("data     = [%p]\n", stk->data);

    PRINT_LOG("\t{\n");

    PRINT_LOG("\t*[CANARY] = %lu\n", stk->left_canary[0]);

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

    PRINT_LOG("\t*[CANARY] = %ld\n", stk->right_canary[0]);

    PRINT_LOG("\t}\n");

    PRINT_LOG("}\n\n");
}

//=========================================================================================================

void close_stack_logs()
{
    fclose(LOG_FILE);
}
