#include "InputOutput.h"

//=============================================================================================================

int open_file(Onegin* onegin, const char* filename)
{
    onegin->mainfile = fopen(filename, "r");

    if(onegin->mainfile == nullptr)
    {
        onegin->error_code = ERROR_OPEN_MAINFILE;

        onegin_dtor(onegin);

        return ERROR_OPEN_MAINFILE;
    }

    return 0;
}

//=============================================================================================================

int left_sort_output(Onegin* onegin)
{
    onegin->left_comp = fopen("sorted text from left.txt", "w");

    if(onegin->left_comp == nullptr)
    {
        return ERROR_LEFT_COMPARATOR_NULLPTR;
    }

    fputs("//======================================================================//\n"
          "//                    sorted text from left to right                    //\n"
          "//======================================================================//\n"
          "\n\n", onegin->left_comp);

    for(size_t i = 0; i < onegin->strings_num; i++)
    {
        fputs(onegin->structs_arr[i].string_ptr, onegin->left_comp);
        fputc('\n', onegin->left_comp);
    }

    output_source_text(onegin, onegin->left_comp);
    
    return 0;
}

//=============================================================================================================

int right_sort_output (Onegin* onegin)
{
    onegin->right_comp = fopen("sorted text from right.txt", "w");

    if(onegin->right_comp == nullptr)
    {
        return ERROR_RIGHT_COMPARATOR_NULLPTR;
    }

    fputs("//======================================================================//\n"
          "//                    sorted text from right to left                    //\n"
          "//======================================================================//\n"
          "\n\n", onegin->right_comp);

    for(size_t i = 0; i < onegin->strings_num; i++)
    {
        fputs(onegin->structs_arr[i].string_ptr, onegin->right_comp);
        fputc('\n', onegin->right_comp);
    }

    output_source_text(onegin, onegin->right_comp);

    return 0;
}

//=============================================================================================================

void output_source_text(Onegin* onegin, FILE* stream)
{
    fputs("\n\n//=======================================================================//\n"
          "//                              source text                              //\n"
          "//=======================================================================//\n"
          "\n\n", stream);

    for(size_t buff_len = 0; buff_len < onegin->chars_num;)
    {
        size_t cur_strlen = strlen(onegin->buffer_ptr + buff_len);

        fputs(onegin->buffer_ptr + buff_len, stream);

        fputs("\n", stream);

        buff_len += cur_strlen + 1;
    }
}

//=============================================================================================================

int sorting_selection(Onegin* onegin)
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
        case(-1): 
        {
            if(right_sorting(onegin))
            {
                onegin->error_code = ERROR_RIGHT_COMPARATOR_NULLPTR;

                onegin_dtor(onegin);

                return ERROR_RIGHT_COMPARATOR_NULLPTR;
            }

            break;
        }

        case(0):
        {
            if(right_sorting(onegin))
            {
                onegin->error_code = ERROR_RIGHT_COMPARATOR_NULLPTR;

                onegin_dtor(onegin);
                
                return ERROR_RIGHT_COMPARATOR_NULLPTR;
            }

            else if(left_sorting(onegin))
            {
                onegin->error_code = ERROR_LEFT_COMPARATOR_NULLPTR;

                onegin_dtor(onegin);

                return ERROR_LEFT_COMPARATOR_NULLPTR;
            }

            break;
        }

        case(1):
        {
            if(left_sorting(onegin))
            {
                onegin->error_code = ERROR_LEFT_COMPARATOR_NULLPTR;

                onegin_dtor(onegin);

                return ERROR_LEFT_COMPARATOR_NULLPTR;
            }

            break;
        }


        default: 
        {
            onegin->error_code = ERROR_SORTING_TYPE;

            onegin_dtor(onegin);

            return ERROR_SORTING_TYPE;
        }
    }

    return 0;
}
