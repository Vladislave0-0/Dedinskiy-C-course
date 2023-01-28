#include "Stack.h"
#include "StackDebug.h"

//=======================================================================================

int main()
{
    Stack* stk1 = stack_ctor();

    stack_push(stk1, 0);
    stack_print_log(stk1);

    stack_push(stk1, 2);
    stack_print_log(stk1);

    stack_pop(stk1);
    stack_print_log(stk1);
    
    // for push write stack_push(stk1, value);
    // and then write stack_print_log(stk1); to see stack changes in file stack_log.txt

    // for pop write stack_pop(stk1);
    // and then write stack_print_log(stk1); to see stack changes in file stack_log.txt

    stack_dtor(stk1);
}
