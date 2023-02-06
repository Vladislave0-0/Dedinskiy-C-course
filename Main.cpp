#include "InputOutput.h"
#include "Common.h"

//=============================================================================================================

int main()
{
    Onegin Onegin_struct = {};

    constructor(&Onegin_struct, "input.txt");

    if(Onegin_struct.error_code == 0)
    {
    sorting_selection(&Onegin_struct);

    destructor(&Onegin_struct);
    }
}
