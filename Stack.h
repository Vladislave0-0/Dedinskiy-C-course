#include <stdio.h>

typedef int elem_t;

struct Stack{
    size_t capacity = 0;
    size_t size     = 0;
    elem_t* data    = nullptr;
    int error_code  = 0;
};

const elem_t POISON = 1488;
const size_t STACK_POP_RESIZE = 4;

void stack_push(Stack* stk, elem_t elem);

void stack_pop(Stack* stk, elem_t* elem);

void stack_ctor(Stack* stk, size_t capacity);

void stack_dtor(Stack* stk);