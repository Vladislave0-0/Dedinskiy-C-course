#include "OneginDebug.h"

//======================================================================================================================

FILE* ERROR_FILE = nullptr;

//======================================================================================================================

void onegin_dump(struct Onegin* Onegin_struct, const char* file_name, unsigned long line, const char* function_name)
{
    printf("CHECK FILE onegin_errors.txt!");

    ERROR_PRINT("in %s at %s(%ld):\n", function_name, file_name, line);

    ERROR_PRINT("Onegin_struct -> [%p]", Onegin_struct);

    onegin_error_decoder(Onegin_struct);
}

//======================================================================================================================

int onegin_verify(struct Onegin* Onegin_struct)
{
    Onegin_struct->error_code = (Onegin_struct->mainfile == nullptr) * ERROR_OPEN_MAINFILE    +
    (Onegin_struct->chars_number <= 0) * ERROR_CHARS_NUM_BELOW_NULL                           +
    (Onegin_struct->chars_buffer_ptr == nullptr) * ERROR_BUFFER_NULLPTR                       +
    (Onegin_struct->strings_number <= 0) * ERROR_STRINGS_NUM_BELOW_NULL                       +
    (Onegin_struct->structs_arr == nullptr) * ERROR_STRUCTS_ARR_NULLPTR;

    return Onegin_struct->error_code;
}

//======================================================================================================================

void onegin_error_decoder(Onegin* Onegin_struct)
{
    if(Onegin_struct->error_code == 0)
    {
        ERROR_PRINT(" -> (OK)\n");
    }

    else
    {
        if(Onegin_struct->error_code & ERROR_OPEN_MAINFILE)
        {
            ERROR_PRINT(" ERROR_OPEN_MAINFILE.\n");
        }

        if(Onegin_struct->error_code & ERROR_CHARS_NUM_BELOW_NULL)
        {
            ERROR_PRINT(" ERROR_CHARS_NUM_BELOW_NULL.\n");
        }

        if(Onegin_struct->error_code & ERROR_BUFFER_NULLPTR)
        {
            ERROR_PRINT(" ERROR_BUFFER_NULLPTR.\n");
        }

        if(Onegin_struct->error_code & ERROR_STRINGS_NUM_BELOW_NULL)
        {
            ERROR_PRINT(" ERROR_STRINGS_NUM_BELOW_NULL.\n");
        }

        if(Onegin_struct->error_code & ERROR_STRUCTS_ARR_NULLPTR)
        {
            ERROR_PRINT(" ERROR_LEFT_CANERROR_STRUCTS_ARR_NULLPTRARY_DEAD.\n");
        }
    }

    printf("\n\n");
}

//======================================================================================================================

void assert_dtor(Onegin* Onegin_struct)
{
    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        Onegin_struct->structs_arr[i].string_lenght = 0;
        Onegin_struct->structs_arr[i].string_pointer = nullptr;
    }

    Onegin_struct->chars_number         = 0;
    Onegin_struct->strings_number       = 0;
    Onegin_struct->number_of_the_string = 0;

    Onegin_struct->mainfile         = nullptr;

    free(Onegin_struct->chars_buffer_ptr);
    Onegin_struct->chars_buffer_ptr = nullptr;  

    free(Onegin_struct->structs_arr);
    Onegin_struct->structs_arr = nullptr;
}

//======================================================================================================================

void open_errors_file()
{
    ERROR_FILE = fopen("onegin_errors.txt", "w");
}

//======================================================================================================================

void close_errors_file()
{
    fclose(ERROR_FILE);
}
