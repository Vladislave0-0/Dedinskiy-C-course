#include "TextSorting.h"

//=============================================================================================================

void sorting_selection(Onegin* Onegin_struct)
{
    int type_sorting = 0;

    printf("Select a sorting type.\n"
           "— write 1 to sort from the left side;\n"
           "— write 0 for both sorts.\n"
           "— write -1 to sort from the right side;\n\n"
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

//=============================================================================================================

int left_comparator(const void* first_struct, const void* second_struct)
{
    char* first_string  = ((String*)first_struct)->string_pointer;
    char* second_string = ((String*)second_struct)->string_pointer;

    size_t i = 0;
    size_t j = 0;

    if(first_string[i] == '\n' || second_string[j] == '\n')
    {
        return tolower(second_string[j]) - tolower(first_string[i]);
    }

    while(1)
    {
        while(!isalpha(first_string[i]))
            i++;

        while(!isalpha(second_string[j]))
            j++;


        if(tolower(first_string[i]) == tolower(second_string[j]))
        {
            if(first_string[i + 1] == '\n' || second_string[j + 1] == '\n')
            {
                return tolower(first_string[i + 1]) - tolower(second_string[j + 1]);
            }

            else
            {
                i++;
                j++;
            }
        }

        else
        {
            return tolower(first_string[i]) - tolower(second_string[j]);
        }
    }
}

//=============================================================================================================

int right_comparator(const void* first_struct, const void* second_struct)
{
    char* first_string  = ((String*)first_struct)->string_pointer;
    char* second_string = ((String*)second_struct)->string_pointer;

    size_t i = ((String*)first_struct)->string_lenght - 2;
    size_t j = ((String*)second_struct)->string_lenght - 2;

    if(first_string[i] == '\n' || second_string[j] == '\n')
    {
        return tolower(second_string[j]) - tolower(first_string[i]);
    }

    while(1)
    {
        while(!isalpha(first_string[i]))
            i--;

        while(!isalpha(second_string[j]))
            j--;


        if(tolower(first_string[i]) == tolower(second_string[j]))
        {
            if(first_string[i - 1] == '\n' || second_string[j - 1] == '\n')
            {
                return tolower(first_string[i - 1]) - tolower(second_string[j - 1]);
            }

            else
            {
                i--;
                j--;
            }
        }

        else
        {
            return tolower(first_string[i]) - tolower(second_string[j]);
        }
    } 
}

//=============================================================================================================

void left_sorting(Onegin* Onegin_struct)
{
    qsort(Onegin_struct->structs_arr, Onegin_struct->strings_number, sizeof(String), left_comparator);

    left_sort_output(Onegin_struct);
}

//=============================================================================================================

void right_sorting(Onegin* Onegin_struct)
{
    qsort(Onegin_struct->structs_arr, Onegin_struct->strings_number, sizeof(String), right_comparator);

    right_sort_output(Onegin_struct);
}
