#ifndef STACK_H
#define STACK_H

//=========================================================================================================

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>

//=========================================================================================================

#define CANARY_PROTECTION
#define HASH_PROTECTION

#define PRINT_LOG(...) fprintf(stk->log_file, __VA_ARGS__)

//=========================================================================================================

typedef int elem_t;

//=========================================================================================================

const size_t POISON          = 0xDEADDED;
const size_t DATA_CANARY     = 0xDEAD;
const size_t STK_CANARY      = 0xDEDDEAD;
const int DATA_CANARY_AMOUNT = 2;

const size_t STACK_POP_RESIZE = 4;
const size_t RESIZE_FACTOR    = 2;

//=========================================================================================================
/**
 * @brief Stack structure.
 * 
 */
struct Stack
{
    size_t stk_left_can = 0;

    FILE* log_file  = nullptr;  
    size_t capacity = 0;
    size_t size     = 0;

    size_t data_left_can = 0;
    elem_t* data     = nullptr;
    size_t data_right_can = 0;

    int error_code = 0;
    long long data_hash = 0;

    size_t stk_right_can = 0;

};

//=========================================================================================================
/**
 * @brief Notes the code of error in stack.
 * 
 */
enum ErrorCodes
{
    ERROR_STACK_NULLPTR = 1,    //| Stack nullptr error.
    ERROR_LOG_FILE_OPEN = 2,    //| File open error.
    ERROR_DATA_CALLOC   = 3,    //| Stack data creation error.
    ERROR_DATA_REALLOC  = 4,    //| Stack dara reallocation error.
};

//=========================================================================================================
/**
 * @brief Creates and initializes stack.
 * 
 * @param stk the stack pointer
 * @return int error
 */
int stack_ctor(Stack* stk);

//=========================================================================================================
/**
 * @brief Pushes the value in the stack.
 * 
 * @param stk the stack pointer
 * @param elem the value to push onto the stack
 */
void stack_push(Stack* stk, elem_t elem);

//=========================================================================================================
/**
 * @brief Deletes the value of the stack.
 * 
 * @param stk the stack pointer
 */
void stack_pop(Stack* stk, elem_t* elem);

//=========================================================================================================
/**
 * @brief Recreates the stack taking into account the degree of fullness.
 * 
 * @param stk the stack pointer
 * @param new_capacity new stack capacity
 */
void stack_resize(Stack* stk, size_t new_capacity);

//=========================================================================================================
/**
 * @brief Fills the fields of the stack with NAN value after its creation and after resize in some range.
 * 
 * @param stk the stack pointer
 * @param start the start of filling stack with NAN value
 * @param finish the end of filling stack with NAN value
 */
void fill_with_POISON(Stack* stk, size_t start, size_t finish);

//=========================================================================================================
/**
 * @brief Opens file stack_log.txt.
 * 
 * @param stk the stack pointer
 * @return int error
 */
int open_log_file(Stack* stk);

//=========================================================================================================
/**
 * @brief Writes the state of the stack at the current moment of code execution in file stack_log.txt.
 * 
 * @param stk the stack pointer
 */
void stk_print_log(Stack* stk);

//=========================================================================================================
/**
 * @brief Prints the time of the current run in file stack_log.txt.
 * 
 */
void stack_time(Stack* stk);

//=========================================================================================================
/**
 * @brief Removes the stack, fills stack fields with POISON value, frees memory.
 * 
 * @param stk the stack pointer
 */
void stack_dtor(Stack* stk);

//=========================================================================================================

#endif
