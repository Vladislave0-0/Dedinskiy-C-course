#include "InputOutput.h"

//=============================================================================================================

int open_file(Onegin* Onegin_struct, const char* filename)
{
    FILE* file_input = fopen(filename, "r");

    if(file_input == nullptr)
    {
        return ERROR_OPEN_MAINFILE;
    }

    Onegin_struct->mainfile = file_input;

    return 0;
}

//=============================================================================================================

int left_sort_output(Onegin* Onegin_struct)
{
    FILE* left_comparator = fopen("sorted text from left.txt", "w");

    if(left_comparator == nullptr)
    {
        return ERROR_LEFT_COMPARATOR_NULLPTR;
    }

    fputs("//======================================================================//\n"
          "//                    sorted text from left to right                    //\n"
          "//======================================================================//\n"
          "\n\n", left_comparator);

    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        fputs(Onegin_struct->structs_arr[i].string_pointer, left_comparator);
        fputc('\n', left_comparator);
    }

    output_source_text(Onegin_struct, left_comparator);
    
    fclose(left_comparator);

    return 0;
}

//=============================================================================================================

int right_sort_output (Onegin* Onegin_struct)
{
    FILE* right_comparator = fopen("sorted text from right.txt", "w");

    if(right_comparator == nullptr)
    {
        return ERROR_RIGHT_COMPARATOR_NULLPTR;
    }

    fputs("//======================================================================//\n"
          "//                    sorted text from right to left                    //\n"
          "//======================================================================//\n"
          "\n\n", right_comparator);

    for(size_t i = 0; i < Onegin_struct->strings_number; i++)
    {
        fputs(Onegin_struct->structs_arr[i].string_pointer, right_comparator);
        fputc('\n', right_comparator);
    }

    output_source_text(Onegin_struct, right_comparator);

    fclose(right_comparator);

    return 0;
}

//=============================================================================================================

void output_source_text(Onegin* Onegin_struct, FILE* stream)
{
    fputs("//=======================================================================//\n"
          "//                              source text                              //\n"
          "//=======================================================================//\n"
          "\n\n", stream);

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

int sorting_selection(Onegin* Onegin_struct)
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
    case -1: 
        if(right_sorting(Onegin_struct))
        {
            printf("Error code: %d.\n", ERROR_RIGHT_COMPARATOR_NULLPTR);
            return ERROR_RIGHT_COMPARATOR_NULLPTR;
        }

        break;

    case  0: 
        if(right_sorting(Onegin_struct))
        {
            printf("Error code: %d.\n", ERROR_RIGHT_COMPARATOR_NULLPTR);
            return ERROR_RIGHT_COMPARATOR_NULLPTR;
        }

        if(left_sorting(Onegin_struct))
        {
            printf("Error code: %d.\n", ERROR_LEFT_COMPARATOR_NULLPTR);
            return ERROR_LEFT_COMPARATOR_NULLPTR;
        }

        break;

    case  1: 
        if(left_sorting(Onegin_struct))
        {
            printf("Error code: %d.\n", ERROR_LEFT_COMPARATOR_NULLPTR);
            return ERROR_LEFT_COMPARATOR_NULLPTR;
        }

        break;

    default: printf("Error sorting type. Please, try again.\n");
        break; 
    }

    return 0;
}
