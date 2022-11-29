#include <stdio.h>
#include <stdlib.h>

//=======================================================================================================================================================

unsigned int my_strlen(const char* str);                              //| Returns the length of the string with the null terminator as a character of the string.
unsigned int my_null_strlen(const char* str);                         //| Returns the length of the string without the null terminator as a character of the string.
int my_puts(const char* str);                                         //| Appends the newline character to the output.
char* my_strchr(char* str, char chr);                                 //| Returns pointer to the found character in str, or null pointer if no such character is found.
char* my_strcpy(char* dest, const char* src);                         //| Returns a copy of src.
char* my_strncpy(char* dest, const char* src, size_t n);              //| Returns a copy of src up to some character n.
char* my_strcat(char* dest, const char* append);                      //| Appends to the string pointed to by the destination argument the string pointed to by the append argument.
char* my_strncat(char* dest, const char* append, size_t n);           //| Appends to the string pointed to by the destination argument the string pointed to by the append argument up to some character n.
const char* my_fgets(FILE* stream, size_t size_of_dest, char* dest);  //| In case of successful reading of the line, a pointer to the array is returned, in which the read data is placed.
char* my_strdup(char* src);                                           //| Duplication of a line with allocation of memory for a new line.
size_t my_getline(char* lineptr, size_t* n, FILE* stream);            //| Reads characters from an input stream and places them into a string.

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

    printf("Result of STRLEN without \"\\0\" for string \"World hello\": %d.\n", my_strlen(string));
    printf("Result of STRLEN with \"\\0\" for string \"World hello\": %d.\n\n", my_null_strlen(string));

//=====================================================================PUTS==============================================================================

    printf("Result of PUTS for string \"World hello\": ");
    printf(".\nNumber of characters %d.\n\n", my_puts(string));

//====================================================================STRCHR=============================================================================

    printf("Result of STRCHR for string \"World hello\" and chr \"H\": ");
    printf("%d.\n", my_strchr(string, 'H'));
    printf("Result of STRCHR for string \"World hello\" and chr \"h\": ");
    printf("%d.\n\n", my_strchr(string, 'h') - string);

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
    FILE* file1 = fopen("test_strdup.txt", "w");
    fprintf(file1, "Perfectly imperfect\n");
    fclose(file1);
    file1 = fopen("test_strdup.txt", "r");
    printf("Result of FGETS: %s.\n\n", my_fgets(file1, 128, dest6));
    fclose(file1);

//=====================================================================STRDUP============================================================================

    char dest7[128] = "meow";
    char* result = my_strdup(dest7);
    printf("Result of STRDUP: %s.\n\n", result);
    free(result);

//=====================================================================GETLINE===========================================================================

    FILE* file2 = fopen("test_getline.txt", "w");
    fprintf(file2, "Take me to ilab please\n");
    fclose(file2);
    file2 = fopen("test_getline.txt", "r");
    size_t n = 15;
    char* dest8 = (char*)calloc(n, sizeof(char));
    printf("Result of getline: %d.\n\n", my_getline(dest8, &n, file2));
    free(dest8);
    fclose(file2);  
    printf("Eto pizdec. Slava bogam ya eto zakonchil.\n");
}

//==============================================================================

unsigned int my_strlen(const char* str){
    unsigned int sum = 0;

    while (str[sum] != '\0'){
        sum++;
    }

    return sum;
}

//==============================================================================

unsigned int my_null_strlen(const char* str){
    unsigned int sum = 0;

    while (str[sum] != '\0'){
        sum++;
    }

    return sum + 1;
}

//==============================================================================

int my_puts(const char* str){
    unsigned int i = 0;

    if (my_strlen(str) != 0){
        for (; i < my_strlen(str); i++){
            putchar(str[i]);
        }
    }

    return i;
}

//==============================================================================

char* my_strchr(char* str, char chr){
    for(int i = 0; str[i] != '\0'; i++){
        if (str[i] == chr)
            return str + i + 1;
    }

    return NULL;
}

//==============================================================================

char* my_strcpy(char* dest, const char* src){
    int i = 0;
    do{
        dest[i] = src[i];
        i++;
    } while(src[i] != '\0') 
        ;
    
    for(; i <= my_strlen(dest); i++){
        dest[i] = '\0';
    }

    return dest;
}

//==============================================================================

char* my_strncpy(char* dest, const char* src, size_t n){
    for(int i = 0; i <= my_strlen(dest); i++){
        if (i < n){
            dest[i] = src[i];
        }
    }
    
    for(; i <= my_strlen(dest); i++){
        dest[i] = '\0';
    }

    return dest;
}

//==============================================================================

char* my_strcat(char* dest, const char* append){
    int i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0')
        ;  
    
    return dest;
}

//==============================================================================

char* my_strncat(char* dest, const char* append, size_t n){
    int i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0'){
        if (j == n)
            return dest;
    }
    
    return dest;
}

//==============================================================================

const char* my_fgets(FILE* stream, size_t size_of_dest, char* dest){
    if (stream != NULL){
        int ch = fgetc(stream);    
        const char* dest_start = dest;

        while ((ch != '\n') && (ch != EOF) && ((dest - dest_start) < size_of_dest)){
            *dest = ch;
            dest++;
            ch = fgetc(stream);
        }

        *dest = '\0';

        return dest_start;
    }

    else{
        return nullptr;
    }
}

//==============================================================================

char* my_strdup(char* src){
    int length = my_null_strlen(src);

    char* dest = (char*)calloc(length, sizeof(char));

    my_strncpy(dest, src, length);

    return dest;
}

//==============================================================================

size_t my_getline(char* lineptr, size_t* n, FILE* stream){
    
    rewind(stream); 

    int characters_number  = 0;
    int сheck = 0;

    
    if (lineptr == NULL){

        while (сheck == 0){

            int ch = fgetc(stream);

            if (ch == '\n'){

                characters_number++;

                сheck++;

                break;
            }

            else if (ch == EOF){

                сheck++;

                break;
            }

            else{
                characters_number++;
            }
        }

        char* dest = (char*)calloc(characters_number + 1, sizeof(char));

        for(int i = 0; i < characters_number; i++){
            dest[i] = getc(stream);
        }

        dest[characters_number] = '\0';

        return characters_number;
    }

    else if (lineptr != NULL){

        rewind(stream); 

        int check = 0;

        int characters_number  = 0;

        size_t buffer_size = *n;

        while (check == 0){

            int ch = fgetc(stream);

            if (ch == '\n'){

                characters_number++;

                сheck++;

                break;
            }

            else if (ch == EOF){

                сheck++;

                break;
            }

            else{
                characters_number++;
            }
        }

        if (buffer_size >= characters_number + 1){

            for(int i = 0; i < characters_number; i++)
                lineptr[i] = getc(stream);

            lineptr[characters_number] = '\0';

            return characters_number;

        }

        else{

            lineptr = (char*)realloc(lineptr, (characters_number + 1)*sizeof(char));

            for(int i = 0; i < characters_number; i++)
                lineptr[i] = getc(stream);

            lineptr[characters_number] = '\0';

            return characters_number;
        }
    }

    else{
        return -1;
    }
}
