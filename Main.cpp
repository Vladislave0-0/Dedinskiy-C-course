#include "StringFunctions.h"

//=======================================================================================================================================================

int main(){

    char string[12] = "World hello";

    char dest1[18] = "I don't wonna die";
    char dest2[18] = "I don't wonna die";

    char dest3[20] = "I love ";
    char dest4[20] = "I love ";
    char dest5[20] = "I love ";
    char append[4] = "you";

//====================================================================STRLEN=============================================================================

    printf("\nResult of STRLEN without \"\\0\" for string \"World hello\": %lu.\n", my_strlen(string));
    printf("Result of STRLEN with \"\\0\" for string \"World hello\": %lu.\n\n", my_null_strlen(string));

//=====================================================================PUTS==============================================================================

    printf("Result of PUTS for string \"World hello\": ");
    printf(".\nNumber of characters %lu.\n\n", my_puts(string));

//====================================================================STRCHR=============================================================================

    printf("Result of STRCHR for string \"World hello\" and chr \"H\": ");
    printf("%s.\n", my_strchr(string, 'H'));
    printf("Result of STRCHR for string \"World hello\" and chr \"h\": ");
    printf("%ld.\n\n", my_strchr(string, 'h') - string);

//=================================================================STRCPY_STRNCPY========================================================================

    printf("Result of STRCPY for src \"World hello\" and dest \"I don't wonna die\": %s.\n", my_strcpy(dest1, string));
    printf("Result of STRNCPY for src \"World hello\" and dest \"I don't wonna die\" for first 5 letters: %s.\n", my_strncpy(dest2, string, 5));
    printf("Result of STRNCPY for src \"World hello\" and dest \"I don't wonna die\" for first 10 letters: %s.\n\n", my_strncpy(dest2, string, 10));

//=================================================================STRCAT_STRNCAT========================================================================

    printf("Result of STRCAT for dest \"I love \" and append \"you\": %s.\n", my_strcat(dest3, append));
    printf("Result of STRNCAT for dest \"I love \", append \"you\" and n = 1: %s.\n", my_strncat(dest4, append, 1));
    printf("Result of STRNCAT for dest \"I love \", append \"you\" and n = 2: %s.\n\n", my_strncat(dest5, append, 2));

//=====================================================================FGETS=============================================================================

    char dest6[128] = {};

    FILE* file1 = fopen("test_fgets.txt", "w");
    fprintf(file1, "Perfectly imperfect");
    fclose(file1);
    file1 = fopen("test_fgets.txt", "r");

    printf("Result of FGETS: %s.\n\n", my_fgets(file1, 128, dest6));
    fclose(file1);

//=====================================================================STRDUP============================================================================

    char dest7[128] = "meow";
    char* result = my_strdup(dest7);
    printf("Result of STRDUP: %s.\n\n", result);
    free(result);

//=====================================================================GETLINE===========================================================================

    FILE* file2 = fopen("test_getline.txt", "w");
    fprintf(file2, "PIZDEC");
    fclose(file2);
    file2 = fopen("test_getline.txt", "r");

    size_t n = 15;
    char* dest8 = (char*)calloc(n, sizeof(char));
    char* dest666 = dest8;
    
    if((dest8 == nullptr) || (n == 0))
    {
        printf("Result of GETLINE: %lu.\n", my_getline(&dest8, &n, file2));
        printf("Result of GETLINE: %s.\n\n", dest8);

        free(dest666);
    }

    else
    {
        printf("Result of GETLINE: %lu.\n", my_getline(&dest8, &n, file2));
        printf("Result of GETLINE: %s.\n\n", dest8);    
    }

    free(dest8);
    fclose(file2);
}
