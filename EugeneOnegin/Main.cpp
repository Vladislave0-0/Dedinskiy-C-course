#include "InputOutput.h"
#include "OneginProcessing.h"

//============================================================

int main()
{
    Onegin onegin = {};

    switch(onegin_ctor(&onegin, "input.txt"))
    {
        case(0):
        {
            switch(sorting_selection(&onegin))
            {
                case(0):
                {
                    onegin_dtor(&onegin);

                    return 0;
                }
                case(ERROR_LEFT_COMPARATOR_NULLPTR):
                {
                    printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_LEFT_COMPARATOR_NULLPTR);

                    return 0;
                }

                case(ERROR_RIGHT_COMPARATOR_NULLPTR):
                {
                    printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_LEFT_COMPARATOR_NULLPTR);

                    return 0;
                }

                case(ERROR_SORTING_TYPE):
                {
                    printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_SORTING_TYPE);

                    return 0;                    
                }

                default:
                {
                    printf("UNKNOWN ERROR!\n");

                    return 0;
                }
            }
        }

        case(ERROR_OPEN_MAINFILE):
        {
            printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_OPEN_MAINFILE);

            return 0;
        }

        case(ERROR_FSTAT_SIZE):
        {
            printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_FSTAT_SIZE);
            
            return 0;
        }

        case(ERROR_BUFFER_NULLPTR):
        {
            printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_BUFFER_NULLPTR);

            return 0;
        }

        case(ERROR_FREAD):
        {
            printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_FREAD);
            
            return 0;
        }

        case(ERROR_STRUCTS_ARR_NULLPTR):
        {
            printf("Error code: %d. Check file \"OneginProcessing.h\" to decipher the error code.\n", ERROR_STRUCTS_ARR_NULLPTR);

            return 0;
        }

        default:
        {
            printf("UNKNOWN ERROR!\n");

            return 0;
        }
    }
}
