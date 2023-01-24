#ifndef STACK_H
#define STACK_H

//=========================================================================================================

#include <stdio.h>

//=========================================================================================================

#define PRINT_LOG(...) fprintf(LOG_FILE, __VA_ARGS__)

#define STACK_DUMP(stack_ptr) stack_dump(stack_ptr, __FILE__, __LINE__, __PRETTY_FUNCTION__)

//=========================================================================================================

typedef double elem_t;

struct Stack{
    size_t capacity = 0;
    size_t size     = 0;
    elem_t* data    = nullptr;
    int error_code  = 0;
};

//=========================================================================================================

const elem_t POISON = 1488;
const size_t STACK_POP_RESIZE = 4;
const size_t RESIZE_FACTOR = 2;

//=========================================================================================================

void stack_ctor(Stack* stk, size_t capacity);

void stack_dtor(Stack* stk);

void stack_push(Stack* stk, elem_t elem);

void stack_pop(Stack* stk, elem_t* elem);

void stack_resize(Stack* stk, size_t new_capacity);

void fill_with_NAN(Stack* stk, size_t start, size_t finish);

//=========================================================================================================

#endif