#include "TextSorting.h"

//=============================================================================================================

int left_comparator(const void* first_struct, const void* second_struct)
{
    char* first_string  = ((const String*)first_struct)->string_pointer;
    char* second_string = ((const String*)second_struct)->string_pointer;

    size_t i = 0;
    size_t j = 0;

    while(1)
    {
        if(first_string[i] == '\0' || second_string[j] == '\0')
        {
            return tolower(second_string[j]) - tolower(first_string[i]);
        }

        while(!isalpha(first_string[i]))
            i++;

        while(!isalpha(second_string[j]))
            j++;

        if(tolower(first_string[i]) == tolower(second_string[j]))
        {
            if(first_string[i + 1] == '\0' || second_string[j + 1] == '\0')
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
    
    return 0;
}

//=============================================================================================================

int right_comparator(const void* first_struct, const void* second_struct)
{
    char* first_string  = ((const String*)first_struct)->string_pointer;
    char* second_string = ((const String*)second_struct)->string_pointer;

    size_t i = ((const String*)first_struct)->string_lenght - 2;
    size_t j = ((const String*)second_struct)->string_lenght - 2;

    while(1)
    {
        if(first_string[i] == '\0' || second_string[j] == '\0')
        {
            return tolower(second_string[j]) - tolower(first_string[i]);
        }

        while(!isalpha(first_string[i]))
            i--;

        while(!isalpha(second_string[j]))
            j--;

        if(tolower(first_string[i]) == tolower(second_string[j]))
        {
            if(first_string[i - 1] == '\0' || second_string[j - 1] == '\0')
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

    return 0;
}

//=============================================================================================================

void left_sorting(Onegin* Onegin_struct)
{
    qsort(Onegin_struct->structs_arr, Onegin_struct->strings_number, sizeof(String), left_comparator);

    left_sort_output(Onegin_struct);

    return;
}

//=============================================================================================================

void right_sorting(Onegin* Onegin_struct)
{
    qsort(Onegin_struct->structs_arr, Onegin_struct->strings_number, sizeof(String), right_comparator);

    right_sort_output(Onegin_struct);

    return;
}
