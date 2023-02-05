#include "InputOutput.h"

//=============================================================================================================

FILE* file_open(const char* filename)
{
    FILE* file_input = fopen(filename, "r");

    assert(file_input != nullptr);

    return file_input;
}

//=============================================================================================================

void num_of_chars(Onegin* Onegin_struct, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    Onegin_struct->chars_number = buf.st_size + 1;

    return;
}

//=============================================================================================================

void chars_buffer(Onegin* Onegin_struct, FILE* stream)
{
    Onegin_struct->chars_buffer_ptr = (char*)calloc(Onegin_struct->chars_number, sizeof(char));

    fread(Onegin_struct->chars_buffer_ptr, sizeof(char), Onegin_struct->chars_number - 1, stream);

    Onegin_struct->chars_buffer_ptr[Onegin_struct->chars_number - 1] = '\0';

    return;
}

//=============================================================================================================

void input_processing(Onegin* Onegin_struct, const char* filename)
{
    FILE* mainfile = file_open(filename);
    assert(mainfile != nullptr);

    num_of_chars(Onegin_struct, filename);

    chars_buffer(Onegin_struct, mainfile);

    num_of_strings(Onegin_struct);

    fclose(mainfile);

    return;
}

//=============================================================================================================

void left_sort_output(Onegin* Onegin_struct)
{
    FILE* left_comparator = fopen("sorted text from left.txt", "w");

    fprintf(left_comparator, "//======================================================================//\n"
                             "//                    sorted text from left to right                    //\n"
                             "//======================================================================//\n"
                             "\n\n");

    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        fputs(Onegin_struct->structs_arr[i].string_pointer, left_comparator);
        fputc('\n', left_comparator);
    }


    fprintf(left_comparator, "//=======================================================================//\n"
                             "//                              source text                              //\n"
                             "//=======================================================================//\n"
                             "\n\n");

    output_source_text(Onegin_struct, left_comparator);
    
    fclose(left_comparator);

    return;
}

//=============================================================================================================

void right_sort_output (Onegin* Onegin_struct)
{
    FILE* right_comparator = fopen("sorted text from right.txt", "w");

    fprintf(right_comparator, "//======================================================================//\n"
                              "//                    sorted text from right to left                    //\n"
                              "//======================================================================//\n"
                              "\n\n");

    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        fputs(Onegin_struct->structs_arr[i].string_pointer, right_comparator);
        fputc('\n', right_comparator);
    }

    output_source_text(Onegin_struct, right_comparator);

    fclose(right_comparator);

    return;
}

//=============================================================================================================

void output_source_text(Onegin* Onegin_struct, FILE* stream)
{
    for(size_t i = 0; i < Onegin_struct->chars_number; i++)
    {
        if(Onegin_struct->chars_buffer_ptr[i] != '\0')
        {
            fputc(Onegin_struct->chars_buffer_ptr[i], stream);
        }

        else
        {
            fputc('\n', stream);
        }
    }
}

//=============================================================================================================

void sorting_selection(Onegin* Onegin_struct)
{
    int type_sorting = 0;

    printf("Select a sorting type:\n"
           "— write 1 to sort from the left side;\n"
           "— write 0 for both sorts;\n"
           "— write -1 to sort from the right side.\n\n"
           "Sorting: ");

    scanf("%d", &type_sorting);

    switch(type_sorting)
    {
    case -1: right_sorting(Onegin_struct);
        break;

    case  0: right_sorting(Onegin_struct); left_sorting(Onegin_struct); 
        break;

    case  1: left_sorting(Onegin_struct);
        break;

    default: printf("Error sorting type. Please, try again.\n");
        break; 
    }
}
