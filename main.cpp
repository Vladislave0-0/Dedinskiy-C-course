#include "Stack.h"
#include "StackDebug.h"

int main()
{
    Stack stk = {};
    int a = 0;

    if(stack_ctor(&stk) == 0)
    {
        stack_push(&stk, 20);
        stack_push(&stk, 20);
        stack_pop(&stk, &a);

        // write here...

        stack_dtor(&stk);
    }
}

// for push write stack_push(&stk, value);
// and then write stack_print_log(&stk); to see stack changes in file stack_log.txt

// for pop write stack_pop(&stk);
// and then write stack_print_log(&stk); to see stack changes in file stack_log.txt
