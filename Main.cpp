#include "InputOutput.h"
#include "Common.h"
#include "TextSorting.h"

//=============================================================================================================

int main()
{
    Onegin Onegin_struct = {};

    input_processing(&Onegin_struct, "input.txt");

    fill_in_structs(&Onegin_struct);

    sorting_selection(&Onegin_struct);

    destructor(&Onegin_struct);
}
