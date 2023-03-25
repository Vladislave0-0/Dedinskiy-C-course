#ifndef STACK_H
#define STACK_H

//=========================================================================================================

#include <stdio.h>
#include <assert.h>

//=========================================================================================================

#define PRINT_LOG(...) fprintf(LOG_FILE, __VA_ARGS__)

#define STACK_DUMP(stack_ptr) stack_dump(stack_ptr, __FILE__, __LINE__, __PRETTY_FUNCTION__)

//=========================================================================================================

typedef int elem_t;

//=========================================================================================================

const elem_t POISON = 0xDEADDED;
const size_t CANARY = 0xDEAD;

const size_t STACK_POP_RESIZE = 4;
const size_t RESIZE_FACTOR    = 2;

//=========================================================================================================

struct Stack{
    void* stack_ptr  = nullptr;
    elem_t* data     = nullptr;
    size_t capacity  = 0;
    size_t size      = 0;
    int error_code   = 0;

    long long data_hash = 0;

    size_t* left_canary = nullptr;
    size_t* right_canary = nullptr;
};

//=========================================================================================================
/**
 * @brief Notes the code of error in stack.
 * 
 */
enum ErrorCodes
{
    STACK_NULLPTR             = 1,    //| Stack nullptr error.
    STACK_CAPACITY_BELOW_NULL = 2,    //| Incorrect value of stack capacity.
    STACK_LOGS_NULLPTR        = 3,    //| File open error.
    STACK_DATA_NULLPTR        = 4,    //| Stack data creation error.
};

//=========================================================================================================
/**
 * @brief Creates and initializes stack.
 * 
 * @param stk the stack pointer
 * @return int
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
 * @brief Removes the stack, fills stack fields with POISON value, frees memory.
 * 
 * @param stk the stack pointer
 */
void stack_dtor(Stack* stk);

//=========================================================================================================

#endif
