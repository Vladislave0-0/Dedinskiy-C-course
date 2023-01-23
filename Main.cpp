#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

int main()
{
    open_stack_logs();
    Stack stk1 = {};

    double result = 0;

    size_t capacity = 10;

    stack_ctor(&stk1, capacity);

    for(size_t i = 0; i < capacity*5; i++)
    {
        stack_push(&stk1, i);
        stack_print(&stk1);   
    }

    close_stack_logs();

    stack_dtor(&stk1);
}
