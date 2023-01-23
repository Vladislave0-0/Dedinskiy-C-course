#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

int main()
{
    Stack stk1 = {};

    double result = 0;

    stack_ctor(&stk1, 10);
    stack_push(&stk1, 1);
    stack_push(&stk1, 4);
    stack_push(&stk1, 88);
    stack_pop(&stk1, &result);

    open_stack_logs();
    stack_print(&stk1);
    close_stack_logs();

    stack_dtor(&stk1);
}
