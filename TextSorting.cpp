#include "TextSorting.h"

//=============================================================================================================

int left_comparator(const void* first_struct, const void* second_struct)
{
    char* first_string  = ((const String*)first_struct)->string_ptr;
    char* second_string = ((const String*)second_struct)->string_ptr;

    size_t i = 0;
    size_t j = 0;

    while(1)
    {
        if(first_string[i] == '\0' || second_string[j] == '\0')
        {
            return tolower(second_string[j]) - tolower(first_string[i]);
        }

        while(!isalpha(first_string[i]))
        {
            i++;
        }

        while(!isalpha(second_string[j]))
        {
            j++;
        }
        
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
    char* first_string  = ((const String*)first_struct)->string_ptr;
    char* second_string = ((const String*)second_struct)->string_ptr;

    size_t i = ((const String*)first_struct)->string_len - 1;
    size_t j = ((const String*)second_struct)->string_len - 1;

    while(1)
    {
        if(first_string[i] == '\0' || second_string[j] == '\0')
        {
            return tolower(second_string[j]) - tolower(first_string[i]);
        }

        while(!isalpha(first_string[i]))
        {
            i--;
        }

        while(!isalpha(second_string[j]))
        {
            j--;
        }

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

size_t space_count(char* string)
{
    size_t space_ch = 0;

    for(size_t k = 0; k < strlen(string); k++)
    {
        if(string[k] == ' ')
        {
            space_ch++;
        }
    }    

    return space_ch;
}

//=============================================================================================================

int left_sorting(struct Onegin* onegin)
{
    qsort(onegin->structs_arr, onegin->strings_num, sizeof(String), left_comparator);

    if(left_sort_output(onegin))
    {
        return ERROR_LEFT_COMPARATOR_NULLPTR;
    }

    return 0;
}

//=============================================================================================================

int right_sorting(struct Onegin* onegin)
{
    qsort(onegin->structs_arr, onegin->strings_num, sizeof(String), right_comparator);

    if(right_sort_output(onegin))
    {
        return ERROR_RIGHT_COMPARATOR_NULLPTR;
    }

    return 0;
}
