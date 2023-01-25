#ifndef STACK_H
#define STACK_H

//=========================================================================================================

#include <stdio.h>
#include <assert.h>

//=========================================================================================================

#define PRINT_LOG(...) fprintf(LOG_FILE, __VA_ARGS__)

#define STACK_DUMP(stack_ptr) stack_dump(stack_ptr, __FILE__, __LINE__, __PRETTY_FUNCTION__)

//=========================================================================================================

typedef double elem_t;

struct Stack{
    size_t* left_canary = nullptr;

    void* stack_ptr = nullptr;
    elem_t* data    = nullptr;
    size_t capacity = 0;
    size_t size     = 0;
    int error_code  = 0;

    size_t* right_canary = nullptr;
};

//=========================================================================================================

const elem_t POISON = 1488;
const size_t CANARY = 0xDEAD;

const size_t STACK_POP_RESIZE = 4;
const size_t RESIZE_FACTOR    = 2;

//=========================================================================================================

Stack* stack_ctor(size_t capacity);

void stack_push(Stack* stk, elem_t elem);

void stack_pop(Stack* stk);

void stack_resize(Stack* stk, size_t new_capacity);

void fill_with_NAN(Stack* stk, size_t start, size_t finish);

void stack_dtor(Stack* stk);

//=========================================================================================================

#endif