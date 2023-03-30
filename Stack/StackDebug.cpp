#include "Stack.h"
#include "StackDebug.h"

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
    #ifdef HASH_PROTECTION

        #ifdef CANARY_PROTECTION

        stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR          +
        (stk->size > stk->capacity) * ERROR_STACK_CAPACITY                     +
        (stk->data_left_can != DATA_CANARY) * ERROR_DATA_LEFT_CANARY_DEAD      +
        (stk->data_right_can != DATA_CANARY) * ERROR_DATA_RIGHT_CANARY_DEAD    +
        (stk->stk_left_can != STK_CANARY) * ERROR_STK_LEFT_CANARY_DEAD         +
        (stk->stk_right_can != STK_CANARY) * ERROR_STK_RIGHT_CANARY_DEAD       +
        (stk->data_hash != data_hash(stk)) * ERROR_DATA_HASH;

        #else

        stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR          +
        (stk->size > stk->capacity) * ERROR_STACK_CAPACITY                     +
        (stk->data_hash != data_hash(stk)) * ERROR_DATA_HASH;


        #endif //CANARY_PROTECTION


    #else
        #ifdef CANARY_PROTECTION

        stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR          +
        (stk->size > stk->capacity) * ERROR_STACK_CAPACITY                     +
        (stk->data_left_can != DATA_CANARY) * ERROR_DATA_LEFT_CANARY_DEAD      +
        (stk->data_right_can != DATA_CANARY) * ERROR_DATA_RIGHT_CANARY_DEAD    +
        (stk->stk_left_can != STK_CANARY) * ERROR_STK_LEFT_CANARY_DEAD         +
        (stk->stk_right_can != STK_CANARY) * ERROR_STK_RIGHT_CANARY_DEAD;

        #else

        stk->error_code = (stk->data == nullptr) * ERROR_DATA_NULLPTR          +
        (stk->size > stk->capacity) * ERROR_STACK_CAPACITY;

        #endif //CANARY_PROTECTION

    #endif //HASH_PROTECTION

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

        if(stk->error_code & ERROR_STACK_CAPACITY)
        {
            PRINT_LOG(" ERROR_STACK_CAPACITY.\n");
        }

        #ifdef CANARY_PROTECTION
        if(stk->error_code & ERROR_DATA_LEFT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_DATA_LEFT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_DATA_RIGHT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_DATA_RIGHT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_STK_LEFT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_STK_LEFT_CANARY_DEAD.\n");
        }

        if(stk->error_code & ERROR_STK_RIGHT_CANARY_DEAD)
        {
            PRINT_LOG(" ERROR_STK_RIGHT_CANARY_DEAD.\n");
        }
        #endif //CANARY_PROTECTION

        #ifdef HASH_PROTECTION
        if(stk->error_code & ERROR_DATA_HASH)     
        {
            PRINT_LOG(" ERROR_DATA_HASH.\n");
        }
        #endif //HASH_PROTECTION
    }

    PRINT_LOG("\n\n");
}

//=========================================================================================================

void assert_dtor(Stack* stk)
{
    for(size_t i = 0; i < stk->capacity; i++)
    {
        stk->data[i] = POISON;
    }

    #ifdef CANARY_PROTECTION

    stk->data--;

    #endif //CANARY_PROTECTION

    stk->capacity       = 0;
    stk->size           = 0;
    stk->error_code     = 0;
    stk->data_hash      = 0;
    stk->data_left_can  = 0;
    stk->data_right_can = 0;

    free(stk->data);
    stk->data = nullptr;

    fclose(stk->log_file);
    stk->log_file = nullptr;

    exit(EXIT_FAILURE);
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
