#include "ListFunctions.h"

//================================================================================

int main()
{
    struct list lst = {};

    list_ctor(&lst);

    // Here you can write list functions...

//=============================
    elem_t a = 0;
    push_after(&lst, 0, 10);
    push_after(&lst, 0, 20);
    push_after(&lst, 1, 30);
    push_after(&lst, 2, 40);
    push_after(&lst, 0, 50);
    head_remove(&lst, &a);
    head_remove(&lst, &a);
    head_remove(&lst, &a);
    head_remove(&lst, &a);
    push_after(&lst, 1, 100);
    push_after(&lst, 1, 200);
    push_after(&lst, 1, 300);
//=============================
    
    if(lst.error_code == SUCCESS)
    {
        list_dtor(&lst);
    }
}
