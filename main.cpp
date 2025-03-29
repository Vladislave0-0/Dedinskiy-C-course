#include "Queue.h"

//==========================================================================

int main()
{
    struct queue que = {};

    if(queue_ctor(&que) == 0)
    {
        terminal_menu(&que);

        queue_dtor(&que);
    }
}

// Write in terminal <dot queue_log.dot -Tpng -o "name".png> to get image
