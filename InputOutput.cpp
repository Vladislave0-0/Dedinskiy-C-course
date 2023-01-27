#include "InputOutput.h"

//=============================================================================================================

FILE* file_open()
{
    FILE* file_input = fopen("input.txt", "r");

    if(errno)
    {
        perror("File open error.\n");
        exit(1);
    }

    return file_input;
}

//=============================================================================================================

void num_of_chars(Onegin* Onegin_struct, FILE* stream)
{
    rewind(stream);
    
    fseek(stream, 0, SEEK_END);
    size_t chars_number = ftell(stream);

    rewind(stream);

    Onegin_struct->chars_number = chars_number + 1;
}

//=============================================================================================================

void chars_buffer(Onegin* Onegin_struct, FILE* stream)
{
    Onegin_struct->chars_buffer_ptr = (char*)calloc(Onegin_struct->chars_number, sizeof(char));

    fread(Onegin_struct->chars_buffer_ptr, 1, Onegin_struct->chars_number - 1, stream);

    Onegin_struct->chars_buffer_ptr[Onegin_struct->chars_number - 1] = '\0';
}

//=============================================================================================================

void input_processing(Onegin* Onegin_struct)
{
    FILE* mainfile = file_open();

    num_of_chars(Onegin_struct, mainfile);

    chars_buffer(Onegin_struct, mainfile);

    fclose(mainfile);
}

//=============================================================================================================

void left_sort_output(Onegin* Onegin_struct)
{
    FILE* left_comparator = fopen("sorted text from left.txt", "w");

    fprintf(left_comparator, "//======================================================================//\n"
                             "//                    sorted text from left to right                    //\n"
                             "//======================================================================//\n"
                             "\n\n");

    for(size_t j = 0; j < Onegin_struct->strings_number; j++)
    {
        for(size_t i = 0; i < Onegin_struct->structs_arr[j].string_lenght; i++)
        {
            fprintf(left_comparator, "%c", Onegin_struct->structs_arr[j].string_pointer[i]);
        }
    }

    fprintf(left_comparator, "//=======================================================================//\n"
                             "//                              source text                              //\n"
                             "//=======================================================================//\n"
                             "\n\n");

    fprintf(left_comparator, "%s", Onegin_struct->chars_buffer_ptr);

    fclose(left_comparator);
}

//=============================================================================================================

void right_sort_output (Onegin* Onegin_struct)
{
    FILE* right_comparator = fopen("sorted text from right.txt", "w");

    fprintf(right_comparator, "//======================================================================//\n"
                              "//                    sorted text from right to left                    //\n"
                              "//======================================================================//\n"
                              "\n\n");

    for(size_t j = 0; j < Onegin_struct->strings_number; j++)
    {
        for(size_t i = 0; i < Onegin_struct->structs_arr[j].string_lenght; i++)
        {
            fprintf(right_comparator, "%c", Onegin_struct->structs_arr[j].string_pointer[i]);
        }
    }

    fprintf(right_comparator, "//=======================================================================//\n"
                              "//                              source text                              //\n"
                              "//=======================================================================//\n"
                              "\n\n");

    fprintf(right_comparator, "%s", Onegin_struct->chars_buffer_ptr);

    fclose(right_comparator);
}
