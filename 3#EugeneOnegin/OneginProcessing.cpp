#include "OneginProcessing.h"

//=============================================================================================================

int onegin_ctor(Onegin* onegin, const char* filename)
{
    if(open_file(onegin, filename))
    {
        return ERROR_OPEN_MAINFILE;
    }

    if(num_of_chars(onegin, filename))
    {
        return ERROR_FSTAT_SIZE;
    }

    switch(chars_buffer(onegin, onegin->mainfile))
    {
        case(0):
        {
            break;
        }
        case(ERROR_BUFFER_NULLPTR):
        {
            return ERROR_BUFFER_NULLPTR;
        }

        case(ERROR_FREAD):
        {
            return ERROR_FREAD;
        }

        default:
        {
            return -1;
        }
    }

    num_of_strings(onegin);

    if(fill_in_structs(onegin))
    {
        return ERROR_STRUCTS_ARR_NULLPTR;
    }

    return 0;
}

//=============================================================================================================

int num_of_chars(Onegin* onegin, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    if(buf.st_size <= 0)
    {
        onegin->error_code = ERROR_FSTAT_SIZE;

        onegin_dtor(onegin);

        return ERROR_FSTAT_SIZE;
    }

    onegin->chars_num = buf.st_size + 1; 

    return 0;
}

//=============================================================================================================

int chars_buffer(Onegin* onegin, FILE* stream)
{
    onegin->buffer_ptr = (char*)calloc(onegin->chars_num, sizeof(char));

    if(onegin->buffer_ptr == nullptr)
    {
        onegin->error_code = ERROR_BUFFER_NULLPTR;

        onegin_dtor(onegin);
        
        return ERROR_BUFFER_NULLPTR;
    }

    size_t fread_ch = fread(onegin->buffer_ptr, sizeof(char), onegin->chars_num - 1, stream);

    if(fread_ch != onegin->chars_num - 1)
    {
        onegin->error_code = ERROR_FREAD;

        onegin_dtor(onegin);

        return ERROR_FREAD;
    }

    onegin->buffer_ptr[onegin->chars_num - 1] = '\0';

    return 0;
}

//=============================================================================================================

void num_of_strings(Onegin* onegin)
{
    for(size_t ch_num = 0; ch_num < onegin->chars_num; ch_num++)
    {
        if(onegin->buffer_ptr[ch_num] == '\n')
        {
            onegin->buffer_ptr[ch_num] = '\0';

            onegin->strings_num++;
        }
    }

    onegin->strings_num++;
}

//=============================================================================================================

int fill_in_structs(Onegin* onegin)
{
    onegin->structs_arr = (String*)calloc(onegin->strings_num, sizeof(String));

    if(onegin->structs_arr == nullptr)
    {
        onegin->error_code = ERROR_STRUCTS_ARR_NULLPTR;

        onegin_dtor(onegin);
        
        return ERROR_STRUCTS_ARR_NULLPTR;
    }

    size_t ptr_counter = 0;

    for(size_t string = 0; string < onegin->strings_num; string++)
    {
        onegin->structs_arr[string].string_ptr = onegin->buffer_ptr + ptr_counter;

        onegin->structs_arr[string].string_len = strlen(onegin->buffer_ptr + ptr_counter);

        ptr_counter += onegin->structs_arr[string].string_len + 1;
    }

    return 0;
}

//=============================================================================================================

void onegin_dtor(Onegin* onegin)
{
    switch(onegin->error_code)
    {
        case(0):
        {
            for(size_t i = 0; i < onegin->strings_num; i++)
            {
                onegin->structs_arr[i].string_len = 0;
                onegin->structs_arr[i].string_ptr = nullptr;
            }

            onegin->chars_num   = 0;
            onegin->strings_num = 0;
            onegin->error_code  = 0;

            free(onegin->buffer_ptr);
            onegin->buffer_ptr = nullptr;  

            free(onegin->structs_arr);
            onegin->structs_arr = nullptr;

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            if(onegin->left_comp != nullptr)   
            {
                fclose(onegin->left_comp);
                onegin->left_comp = nullptr;
            } 

            if(onegin->right_comp != nullptr)   
            {
                fclose(onegin->right_comp);
                onegin->right_comp = nullptr;
            } 

            break;
        }

        case(ERROR_OPEN_MAINFILE):
        {
            onegin->error_code = 0;

            break;
        }

        case(ERROR_FSTAT_SIZE):
        {
            onegin->error_code = 0;

            
            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            break;
        }

        case(ERROR_BUFFER_NULLPTR):
        {
            onegin->chars_num  = 0;
            onegin->error_code = 0;

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            break;
        }

        case(ERROR_FREAD):
        {
            onegin->chars_num  = 0;
            onegin->error_code = 0;

            free(onegin->buffer_ptr); 
            onegin->buffer_ptr = nullptr;

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            break;
        }

        case(ERROR_STRUCTS_ARR_NULLPTR):
        {
            onegin->chars_num   = 0;
            onegin->strings_num = 0;
            onegin->error_code  = 0;

            free(onegin->buffer_ptr);
            onegin->buffer_ptr = nullptr; 

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            break;
        }

        case(ERROR_LEFT_COMPARATOR_NULLPTR):
        {
            for(size_t i = 0; i < onegin->strings_num; i++)
            {
                onegin->structs_arr[i].string_len = 0;
                onegin->structs_arr[i].string_ptr = nullptr;
            }

            onegin->chars_num   = 0;
            onegin->strings_num = 0;
            onegin->error_code  = 0;

            free(onegin->buffer_ptr);
            onegin->buffer_ptr = nullptr;   

            free(onegin->structs_arr);
            onegin->structs_arr = nullptr;  

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr; 

            if(onegin->right_comp != nullptr)   
            {
                fclose(onegin->right_comp);
                onegin->right_comp = nullptr;
            } 

            break;
        }

        case(ERROR_RIGHT_COMPARATOR_NULLPTR):
        {
            for(size_t i = 0; i < onegin->strings_num; i++)
            {
                onegin->structs_arr[i].string_len = 0;
                onegin->structs_arr[i].string_ptr = nullptr;
            }

            onegin->chars_num   = 0;
            onegin->strings_num = 0;
            onegin->error_code  = 0;

            free(onegin->buffer_ptr);
            onegin->buffer_ptr = nullptr;   

            free(onegin->structs_arr);
            onegin->structs_arr = nullptr;  

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            if(onegin->left_comp != nullptr)   
            {
                fclose(onegin->left_comp);
                onegin->left_comp = nullptr;
            }  

            break;
        }

        case(ERROR_SORTING_TYPE):
        {
            for(size_t i = 0; i < onegin->strings_num; i++)
            {
                onegin->structs_arr[i].string_len = 0;
                onegin->structs_arr[i].string_ptr = nullptr;
            }

            onegin->chars_num   = 0;
            onegin->strings_num = 0;
            onegin->error_code  = 0;

            free(onegin->buffer_ptr);
            onegin->buffer_ptr = nullptr;   

            free(onegin->structs_arr);
            onegin->structs_arr = nullptr;  

            fclose(onegin->mainfile);
            onegin->mainfile = nullptr;

            break;
        }

        default:
        {
            printf("UNKNOWN ERROR FOR onegin_dtor!\n");

            break;
        }
    }
}
