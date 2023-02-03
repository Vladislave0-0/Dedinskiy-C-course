#include "InputOutput.h"
#include "TextSorting.h"

//=============================================================================================================

void num_of_strings(Onegin* Onegin_struct)
{
    size_t chars_number = 0;

    while(chars_number < Onegin_struct->chars_number)
    {

        if(Onegin_struct->chars_buffer_ptr[chars_number] == '\n')
        {
            Onegin_struct->chars_buffer_ptr[chars_number] = '\0';

            Onegin_struct->strings_number++;
        }

        chars_number++;
    }
    
    Onegin_struct->strings_number++;

    return;
}

//=============================================================================================================

#define STR_ARR Onegin_struct->structs_arr
#define STR_NUM Onegin_struct->strings_number
#define CH_BUF  Onegin_struct->chars_buffer_ptr
#define CH_NUM  Onegin_struct->chars_number

void fill_in_structs(Onegin* Onegin_struct)
{
    Onegin_struct->structs_arr = (String*)calloc(Onegin_struct->strings_number, sizeof(String));
    assert(Onegin_struct->structs_arr != nullptr);

    size_t ptr_counter = 0;

    for(size_t string = 0; string < STR_NUM; string++)
    {
        STR_ARR[string].string_pointer = CH_BUF + ptr_counter;

        STR_ARR[string].string_lenght = strlen(CH_BUF + ptr_counter) + 1;

        while(CH_BUF[ptr_counter] != '\0')
        {
            ptr_counter++;
        }

        ptr_counter++;
    }

    return;
}

//=============================================================================================================

void destructor(Onegin* Onegin_struct)
{
    free(Onegin_struct->chars_buffer_ptr);
    Onegin_struct->chars_buffer_ptr = nullptr;

    free(Onegin_struct->structs_arr);
    Onegin_struct->structs_arr = nullptr;

    return;
}
