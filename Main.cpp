#include "InputOutput.h"
#include "Common.h"

//=========================================================

int main()
{
    Onegin Onegin_struct = {};

    if(constructor(&Onegin_struct, "input.txt") == 0)
    {
        sorting_selection(&Onegin_struct);

        destructor(&Onegin_struct);

        return 0;
    }
}
