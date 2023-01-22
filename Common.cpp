
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
            Onegin_struct->strings_number++;
        }

        chars_number++;
    }
}

//=============================================================================================================

void structs_ptr_calloc(Onegin* Onegin_struct)
{
    num_of_strings(Onegin_struct); 

    Onegin_struct->structs_arr = (String*)calloc(Onegin_struct->strings_number, sizeof(String));
}

//=============================================================================================================

#define STR_ARR Onegin_struct->structs_arr
#define STR_NUM Onegin_struct->strings_number
#define CH_BUF  Onegin_struct->chars_buffer_ptr
#define CH_NUM  Onegin_struct->chars_number

void fill_in_structs(Onegin* Onegin_struct)
{
    size_t number_of_char = 0;
    size_t chars_in_string = 0;

    STR_ARR[0].string_pointer = CH_BUF;

    for(size_t string = 1; string < STR_NUM; string++)
    {
        while(CH_BUF[number_of_char] != '\n')
        {
            chars_in_string++;
            number_of_char++;
        }

        number_of_char++;

        STR_ARR[string].string_pointer = CH_BUF + number_of_char;

        STR_ARR[string - 1].string_lenght = chars_in_string + 1;

        chars_in_string = 0;
    }


    STR_ARR[STR_NUM - 1].string_lenght = (CH_BUF + CH_NUM) - STR_ARR[STR_NUM - 1].string_pointer;
}

//=============================================================================================================

void destructor(Onegin* Onegin_struct)
{
    free(Onegin_struct->chars_buffer_ptr);

    free(Onegin_struct->structs_arr);
}
