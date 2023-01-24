#include "Stack.h"
#include "StackDebug.h"

//============================================================

int main()
{
    
    Stack stk1 = {};

    double result = 0;

    size_t capacity = 10;

    stack_ctor(&stk1, capacity);

    for(size_t i = 0; i < capacity*2; i++)
    {
        stack_push(&stk1, i);
        stack_print_log(&stk1);   
    }

    stack_pop(&stk1, &result);    

    stack_dtor(&stk1);
}
