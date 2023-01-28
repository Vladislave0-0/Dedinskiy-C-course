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
/**
 * @brief Notes the type of error in stack.
 * 
 */
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
    ERROR_DATA_HASH                 = 1 << 8,     // stk->data_hash != stack_data_hash(stk)
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
 * @return int 
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
/**
 * @brief Opens the file stack_log.txt in mode "w".
 * 
 */
void open_stack_logs();

//=========================================================================================================
/**
 * @brief Prints all information about the stack at the moment to a file stack_log.txt.
 * 
 * @param stk the stack pointer
 */
void stack_print_log(Stack* stk);

//=========================================================================================================
/**
 * @brief Closes the file stack_log.txt.
 * 
 */
void close_stack_logs();

//=========================================================================================================

#endif
