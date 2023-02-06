#include "Common.h"

//=============================================================================================================

void constructor(Onegin* Onegin_struct, const char* filename)
{
    open_file(Onegin_struct, filename);

    num_of_chars(Onegin_struct, filename);

    chars_buffer(Onegin_struct, Onegin_struct->mainfile);

    num_of_strings(Onegin_struct);

    fill_in_structs(Onegin_struct);

    open_errors_file();
    
    ASSERT_OK(Onegin_struct);
}

//=============================================================================================================

void num_of_chars(Onegin* Onegin_struct, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    Onegin_struct->chars_number = buf.st_size + 1;
}

//=============================================================================================================

void chars_buffer(Onegin* Onegin_struct, FILE* stream)
{
    Onegin_struct->chars_buffer_ptr = (char*)calloc(Onegin_struct->chars_number, sizeof(char));

    fread(Onegin_struct->chars_buffer_ptr, sizeof(char), Onegin_struct->chars_number - 1, stream);

    Onegin_struct->chars_buffer_ptr[Onegin_struct->chars_number - 1] = '\0';
}

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
}

//=============================================================================================================

#define STR_ARR Onegin_struct->structs_arr
#define STR_NUM Onegin_struct->strings_number
#define CH_BUF  Onegin_struct->chars_buffer_ptr
#define CH_NUM  Onegin_struct->chars_number

void fill_in_structs(Onegin* Onegin_struct)
{
    Onegin_struct->structs_arr = (String*)calloc(Onegin_struct->strings_number, sizeof(String));

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
}

//=============================================================================================================

void destructor(Onegin* Onegin_struct)
{
    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        Onegin_struct->structs_arr[i].string_lenght = 0;
        Onegin_struct->structs_arr[i].string_pointer = nullptr;
    }

    Onegin_struct->chars_number         = 0;
    Onegin_struct->strings_number       = 0;
    Onegin_struct->error_code           = 0;
    Onegin_struct->number_of_the_string = 0;

    Onegin_struct->mainfile         = nullptr;

    free(Onegin_struct->chars_buffer_ptr);
    Onegin_struct->chars_buffer_ptr = nullptr;  

    free(Onegin_struct->structs_arr);
    Onegin_struct->structs_arr = nullptr;
}
