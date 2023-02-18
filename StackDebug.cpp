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
    PRINT_LOG("in %s at %s(%lu):\n", function_name, file_name, line);

    PRINT_LOG("Stack[%p]", stk->data);

    stack_error_decoder(stk);
}

//=========================================================================================================

int stack_verify(Stack* stk)
{
    stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR    +
    (stk->stack_ptr == nullptr) * ERROR_STACK_NULLPTR                +
    (stk->size > stk->capacity) * ERROR_SIZE_BIGGER_THAN_CAPACITY    +
    (stk->left_canary[0] != CANARY) * ERROR_LEFT_CANARY_DEAD         +
    (stk->left_canary == nullptr) * ERROR_LEFT_CANARY_NULLPTR        +
    (stk->right_canary[0] != CANARY) * ERROR_RIGHT_CANARY_DEAD       +
    (stk->right_canary == nullptr) * ERROR_RIGHT_CANARY_NULLPTR      +
    (stk->data_hash != data_hash(stk)) * ERROR_DATA_HASH;

    return stk->error_code;
}

//=========================================================================================================

void stack_error_decoder(Stack* stk)
{
    if(stk->error_code == 0)
    {
        PRINT_LOG(" -> (OK)\n");
    }

    else
    {
        if(stk->error_code & ERROR_DATA_NULLPTR)
        {
            PRINT_LOG(" ERROR_DATA_NULLPTR.\n");
        }

        if(stk->error_code & ERROR_STACK_NULLPTR)
        {
            PRINT_LOG(" ERROR_STACK_NULLPTR.\n");
        }

        if(stk->error_code & ERROR_SIZE_BIGGER_THAN_CAPACITY)
        {
            PRINT_LOG(" ERROR_SIZE_BIGGER_THAN_CAPACITY.\n");
        }

        if(stk->error_code & ERROR_LEFT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_LEFT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_LEFT_CANARY_NULLPTR)
        {
            PRINT_LOG(" ERROR_LEFT_CANARY_NULLPTR.\n");
        }   

        if(stk->error_code & ERROR_RIGHT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_RIGHT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_RIGHT_CANARY_NULLPTR)
        {
            PRINT_LOG(" ERROR_RIGHT_CANARY_NULLPTR.\n");
        }     

        if(stk->error_code & ERROR_DATA_HASH)     
        {
            PRINT_LOG(" ERROR_DATA_HASH.\n");
        }    
    }

    printf("\n\n");
}

//=========================================================================================================

void assert_dtor(Stack* stk)
{
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

//=========================================================================================================

long long calculate_hash(elem_t* pointer, size_t size)
{
    long long hash = 0;

    for(size_t i = 0; i < size; i++)
    {
        hash = ((hash << 5) + hash) + pointer[i];
    }

    return hash;
}

//=========================================================================================================

long long data_hash(Stack* stk)
{
    return calculate_hash(stk->data, stk->capacity);
}

//=========================================================================================================

int open_stack_logs()
{
    LOG_FILE = fopen("./Logs/stack_log.txt", "w");

    if(LOG_FILE == nullptr)
    {
        return STACK_LOGS_NULLPTR;
    }

    return 0;
}

//=========================================================================================================

void stack_print_log(Stack* stk)
{
    PRINT_LOG("{\n");

    PRINT_LOG("size      = %lu\n", stk->size);

    PRINT_LOG("capacity  = %lu\n", stk->capacity);

    PRINT_LOG("data      = [%p]\n", stk->data);

    PRINT_LOG("data_hash = [%lld]\n", stk->data_hash);

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