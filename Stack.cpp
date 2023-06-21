#include "Stack.h"
#include "StackDebug.h"

//=========================================================================================================

const size_t INITIAL_STK_CAP = 10;

//=========================================================================================================

int stack_ctor(Stack* stk)
{
    if(stk == nullptr)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_STACK_NULLPTR);
        return ERROR_STACK_NULLPTR;
    }

    stk->capacity = INITIAL_STK_CAP;

    if(open_log_file(stk) != 0)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_LOG_FILE_OPEN);
        return ERROR_LOG_FILE_OPEN;
    }


#ifdef CANARY_PROTECTION

    stk->stk_left_can = STK_CANARY;
    stk->stk_right_can = STK_CANARY;

    stk->data = (elem_t*)calloc(stk->capacity + DATA_CANARY_AMOUNT, sizeof(elem_t));

    if(stk->data == nullptr)
    {
        fclose(stk->log_file);
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_DATA_CALLOC);
        return ERROR_DATA_CALLOC;
    }

    *stk->data = (elem_t)DATA_CANARY;

    stk->data_left_can  = (size_t)*stk->data;
    stk->data_right_can = (size_t)*(stk->data + stk->capacity + 1);
    
    stk->data_left_can = DATA_CANARY;
    stk->data_right_can = DATA_CANARY;

    stk->data++;

#else

    stk->data = (elem_t*)calloc(stk->capacity, sizeof(elem_t));

    if(stk->data == nullptr)
    {
        close_log_file(stk);
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_DATA_CALLOC);
        return ERROR_DATA_CALLOC;
    }

#endif //CANARY_PROTECTION

    fill_with_POISON(stk, 0, stk->capacity);

#ifdef HASH_PROTECTION

    stk->data_hash = data_hash(stk);

#endif

    stk_print_log(stk);

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

#ifdef HASH_PROTECTION

    stk->data_hash = data_hash(stk);

#endif

    stk_print_log(stk);
}

//=========================================================================================================

void stack_pop(Stack* stk, elem_t* elem)
{
    ASSERT_OK(stk);

    stk->size--;

    *elem = stk->data[stk->size];
    
    stk->data[stk->size] = POISON;

#ifdef HASH_PROTECTION

    stk->data_hash = data_hash(stk);

#endif

    if(stk->size * STACK_POP_RESIZE <= stk->capacity)
    {
        stack_resize(stk, (int)(stk->capacity / RESIZE_FACTOR));
    }
    
    stk_print_log(stk);
}

//=========================================================================================================

void stack_resize(Stack* stk, size_t new_capacity)
{  
    ASSERT_OK(stk);

    size_t old_capacity = stk->capacity;
    stk->capacity = new_capacity;

#ifdef CANARY_PROTECTION

    stk->data--;

    stk->data = (elem_t*)realloc(stk->data, (stk->capacity + DATA_CANARY_AMOUNT) * sizeof(elem_t));

    if(stk->data == nullptr)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_DATA_REALLOC);

        exit(ERROR_DATA_REALLOC);
    }

    *stk->data = (elem_t)DATA_CANARY;

    stk->data_left_can  = (size_t)*stk->data;
    stk->data_right_can = (size_t)*(stk->data + stk->capacity + 1);
    
    stk->data_left_can = DATA_CANARY;
    stk->data_right_can = DATA_CANARY;

    stk->data++;

#else

    stk->data = (elem_t*)realloc(stk->data, stk->capacity * sizeof(elem_t));

    if(stk->data == nullptr)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_DATA_REALLOC);

        exit(ERROR_DATA_REALLOC);
    }

#endif //CANARY_PROTECTION



#ifdef HASH_PROTECTION

    stk->data_hash = data_hash(stk);

#endif

    fill_with_POISON(stk, old_capacity, stk->capacity); 

#ifdef HASH_PROTECTION

    stk->data_hash = data_hash(stk);

#endif
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

int open_log_file(Stack* stk)
{
    stk->log_file = fopen("stack_log.txt", "w");

    if(stk->log_file == nullptr)
    {
        return ERROR_LOG_FILE_OPEN;
    }

    return 0;
}

//=========================================================================================================

void stk_print_log(Stack* stk)
{
    PRINT_LOG("{\n");

#ifdef CANARY_PROTECTION
    PRINT_LOG("[STK_CANARY] = %lu\n", stk->stk_left_can);
#endif //CANARY_PROTECTION

    PRINT_LOG("capacity     = %lu\n", stk->capacity);

    PRINT_LOG("size         = %lu\n", stk->size);

#ifdef HASH_PROTECTION
    PRINT_LOG("data_hash    = [%lld]\n", stk->data_hash);
#endif //HASH_PROTECTION

    PRINT_LOG("data         = [%p]\n", stk->data);

    PRINT_LOG("\t{\n");

#ifdef CANARY_PROTECTION
    PRINT_LOG("\t[DATA_CANARY] = %lu\n", stk->data_left_can);
#endif //CANARY_PROTECTION

    for(size_t i = 0; i < stk->capacity; i++)
    {
        if(!isnan(stk->data[i]))
        {
            if(i < stk->size)
            {
                PRINT_LOG("   *[%lu] = " FORM_SPEC "\n", i, stk->data[i]);
            }

            else
            {
                PRINT_LOG("\t[%lu] = " PSN_FORM_SPEC "\t\t\t<-- POISON\n", i, (psn_t)stk->data[i]);
            }
        }

        else 
        {
            PRINT_LOG("\t [%lu] = NAN\n", i);
        }
    }

#ifdef CANARY_PROTECTION
    PRINT_LOG("\t[DATA_CANARY] = %ld\n", stk->data_right_can);
#endif //CANARY_PROTECTION

    PRINT_LOG("\t}\n");

#ifdef CANARY_PROTECTION
    PRINT_LOG("[STK_CANARY] = %lu\n", stk->stk_right_can);
#endif //CANARY_PROTECTION

    PRINT_LOG("}\n\n\n");
}

//=========================================================================================================

void stack_dtor(Stack* stk)
{ 
    ASSERT_OK(stk);

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
}
