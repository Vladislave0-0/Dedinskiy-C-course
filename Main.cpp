#include <stdio.h>
#include "Stack.h"
#include <stdlib.h>

int main()
{
    Stack stk1 = {};

    int result = 0;

    stack_ctor(&stk1, 10);

    stack_push(&stk1, 1);

    stack_push(&stk1, 4);

    stack_push(&stk1, 88);

    stack_pop(&stk1, &result);

    printf("%d\n", result);

    stack_dtor(&stk1);
}
