#include "Common.h"

//=============================================================================================================

int constructor(Onegin* Onegin_struct, const char* filename)
{
    if(open_file(Onegin_struct, filename))
    {
        printf("Error code: %d.\n", ERROR_OPEN_MAINFILE);
        return ERROR_OPEN_MAINFILE;
    }

    if(num_of_chars(Onegin_struct, filename))
    {
        printf("Error code: %d.\n", ERROR_CHARS_NUM_BELOW_NULL);
        return ERROR_CHARS_NUM_BELOW_NULL;
    }

    if(chars_buffer(Onegin_struct, Onegin_struct->mainfile))
    {
        printf("Error code: %d.\n", ERROR_BUFFER_NULLPTR);
        return ERROR_BUFFER_NULLPTR;
    }

    if(num_of_strings(Onegin_struct))
    {
        printf("Error code: %d.\n", ERROR_STRINGS_NUM_BELOW_NULL);
        return ERROR_STRINGS_NUM_BELOW_NULL;
    }

    if(fill_in_structs(Onegin_struct))
    {
        printf("Error code: %d.\n", ERROR_STRUCTS_ARR_NULLPTR);
        return ERROR_STRUCTS_ARR_NULLPTR;
    }

    return 0;
}

//=============================================================================================================

int num_of_chars(Onegin* Onegin_struct, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    if(buf.st_size <= 0)
    {
        return ERROR_CHARS_NUM_BELOW_NULL;
    }

    Onegin_struct->chars_number = buf.st_size + 1;

    return 0;
}

//=============================================================================================================

int chars_buffer(Onegin* Onegin_struct, FILE* stream)
{
    Onegin_struct->chars_buffer_ptr = (char*)calloc(Onegin_struct->chars_number, sizeof(char));

    if(Onegin_struct->chars_buffer_ptr == nullptr)
    {
        free(Onegin_struct->chars_buffer_ptr);
        return ERROR_BUFFER_NULLPTR;
    }

    fread(Onegin_struct->chars_buffer_ptr, sizeof(char), Onegin_struct->chars_number - 1, stream);

    Onegin_struct->chars_buffer_ptr[Onegin_struct->chars_number - 1] = '\0';

    return 0;
}

//=============================================================================================================

int num_of_strings(Onegin* Onegin_struct)
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

    if(Onegin_struct->strings_number <= 0)
    {
        return ERROR_STRINGS_NUM_BELOW_NULL;
    }
    
    Onegin_struct->strings_number++;

    return 0;
}

//=============================================================================================================

#define STRUCTS_ARR Onegin_struct->structs_arr
#define STRINGS_NUM Onegin_struct->strings_number
#define CHARS_BUF  Onegin_struct->chars_buffer_ptr
#define CHARS_NUM  Onegin_struct->chars_number

int fill_in_structs(Onegin* Onegin_struct)
{
    Onegin_struct->structs_arr = (String*)calloc(Onegin_struct->strings_number, sizeof(String));

    if(Onegin_struct->structs_arr == nullptr)
    {
        free(Onegin_struct->structs_arr);
        return ERROR_STRUCTS_ARR_NULLPTR;
    }

    size_t ptr_counter = 0;

    for(size_t string = 0; string < STRINGS_NUM; string++)
    {
        STRUCTS_ARR[string].string_pointer = CHARS_BUF + ptr_counter;

        STRUCTS_ARR[string].string_lenght = strlen(CHARS_BUF + ptr_counter);

        ptr_counter += STRUCTS_ARR[string].string_lenght + 1;
    }

    return 0;
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
