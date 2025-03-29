#ifndef STACK_DEBUG_H
#define STACK_DEBUG_H

//=========================================================================================================

#define STACK_DUMP(stk) stack_dump(stk, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define ASSERT_OK(stk)                                      \
    do                                                      \
    {                                                       \
        if(stack_verify(stk) != 0)                          \
        {                                                   \
            STACK_DUMP(stk);                                \
            assert_dtor(stk);                               \
        }                                                   \
    } while(0) 
     
//=========================================================================================================
/**
 * @brief Notes the type of error in stack.
 * 
 */
enum StackErrors
{
    ERROR_DATA_NULLPTR           = 1 << 0,     //| stk->data == nullptr
    ERROR_STACK_CAPACITY         = 1 << 1,     //| stk->size > stk->capacity
    ERROR_DATA_LEFT_CANARY_DEAD  = 1 << 2,     //| stk->data_left_can != DATA_CANARY
    ERROR_DATA_RIGHT_CANARY_DEAD = 1 << 3,     //| stk->data_right_can != DATA_CANARY
    ERROR_STK_LEFT_CANARY_DEAD   = 1 << 4,     //| stk->stk_left_can != STK_CANARY
    ERROR_STK_RIGHT_CANARY_DEAD  = 1 << 5,     //| stk->stk_right_can != STK_CANARY
    ERROR_DATA_HASH              = 1 << 6,     //| stk->data_hash != stack_data_hash(stk)
};

//=========================================================================================================
/**
 * @brief Prints the error data to the file stack_log.txt.
 * 
 * @param stk the stack pointer
 * @param file_name the name of the file that contains the function
 * @param line line number where the error was found
 * @param function_name the name of the function in which the error was found
 */
void stack_dump(Stack* stk, const char* file_name, size_t line, const char* function_name);

//=========================================================================================================
/**
 * @brief Сonsiders the error code as the sum of errors in binary code.
 * 
 * @param stk the stack pointer
 * @return int stk->error_code
 */
int stack_verify(Stack* stk);

//=========================================================================================================
/**
 * @brief Decodes the error and prints the name of the error to the file.
 * 
 * @param stk the stack pointer
 */
void stack_error_decoder(Stack* stk);

//=========================================================================================================
/**
 * @brief If an error was found in the middle of running the program, this function
 *        removes the stack, fills stack fields with POISON value, frees memory.
 * 
 * @param stk the stack pointer
 */
void assert_dtor(Stack* stk);

//=========================================================================================================
/**
 * @brief Calculates hash given pointer and size.
 * 
 * @param pointer pointer to part of the stack
 * @param size the number of elements over which the hash will be calculated
 * @return long long 
 */
long long calculate_hash(elem_t* pointer, size_t size);

//=========================================================================================================
/**
 * @brief Applies function calculate_hash(...) for calculate hash of stack data.
 * 
 * @param stk the stack pointer
 * @return long long 
 */
long long data_hash(Stack* stk);

//=========================================================================================================

#endif
