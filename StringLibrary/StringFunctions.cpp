#include "StringFunctions.h"

//============================================================================================

size_t my_strlen(const char* str)
{
    size_t sum = 0;

    while (str[sum] != '\0')
        sum++;

    return sum;
}

//============================================================================================

size_t my_puts(const char* str)
{
    size_t i = 0;

    if (my_strlen(str) != 0)
    {
        for (; i < my_strlen(str); i++)
            putchar(str[i]);
    }

    return i;
}

//============================================================================================

char* my_strchr(char* str, char chr)
{
    for(size_t i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == chr)
            return str + i + 1;
    }

    return nullptr;
}

//============================================================================================

char* my_strcpy(char* dest, const char* src)
{
    size_t i = 0;

    do{
        dest[i] = src[i];
        i++;
    } while(src[i] != '\0');
    
    dest[i] = '\0';

    return dest;
}

//============================================================================================

char* my_strncpy(char* dest, const char* src, size_t n)
{
    size_t i = 0;

    for(; i < my_strlen(src); i++)
    {
        if(i < n)
            dest[i] = src[i];
    }
    
    for(; i < n; i++)
        dest[i] = '\0';

    return dest;
}

//============================================================================================

char* my_strcat(char* dest, const char* append)
{
    size_t i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0');  
    
    return dest;
}

//============================================================================================

char* my_strncat(char* dest, const char* append, size_t n)
{
    size_t i = 0, j = 0;

    while(dest[i] != '\0')
        i++;

    while((dest[i++] = append[j++]) != '\0')
    {
        if (j == n)
            return dest;
    }
    
    return dest;
}

//============================================================================================

const char* my_fgets(FILE* stream, size_t size_of_dest, char* dest)
{
    if (stream != NULL)
    {
        int ch = fgetc(stream);

        const char* dest_start = dest;

        while ((ch != '\n') && (ch != EOF) && ((size_t)(dest - dest_start) < size_of_dest))
        {
            *dest = (char)ch;
            dest++;
            ch = fgetc(stream);
        }

        *dest = '\0';

        return dest_start;
    }

    else
    {
        return nullptr;
    }
}

//============================================================================================

char* my_strdup(char* src)
{
    size_t length = my_strlen(src) + 1; // +1 because of '\0' at the end

    char* dest = (char*)calloc(length, sizeof(char));

    my_strncpy(dest, src, length);

    return dest;
}

//============================================================================================

ssize_t my_getdelim(char **lineptr, size_t *n, int delim, FILE* stream)
{
    char* new_lineptr = nullptr;
    char* cur_pos     = nullptr;

    size_t new_lineptr_len = 0;
    int ch                 = 0;

    if (lineptr == nullptr || n == NULL || stream == nullptr) 
    {
        errno = EINVAL; // Invalid argument.
        return -1;
    }

    if (*lineptr == nullptr)
    {
        *n = 128;

        if ((*lineptr = (char *)calloc(*n, sizeof(char))) == nullptr) 
        {
            errno = ENOMEM; // There is not enough memory to execute the requested statement.
            return -1;
        }
    }

    cur_pos = *lineptr;  // We write every char in cur_pos[i]

    for (;;) 
    {
        ch = getc(stream);

        if (ferror(stream) || (ch == EOF && cur_pos == *lineptr))
        {
            return -1;
        }

        if (ch == EOF)
        {
            break;
        }

        if ((*lineptr + *n - cur_pos) < 2) 
        {
            new_lineptr_len = *n * 2;

            if ((new_lineptr = (char *)realloc(*lineptr, new_lineptr_len)) == nullptr) 
            {
                errno = ENOMEM; // There is not enough memory to execute the requested statement.
                return -1;
            }
            
            cur_pos = new_lineptr + (cur_pos - *lineptr); // new_lineptr + num of chars

            *lineptr = new_lineptr;

            *n = new_lineptr_len;
        }

        // printf("%s\n", new_lineptr);

        *(cur_pos++) = (char)ch;

        if(ch == delim)
            break;
    }

    *cur_pos = '\0';

    return (ssize_t)(cur_pos - *lineptr);
}

//============================================================================================

ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) 
{
    return my_getdelim(lineptr, n, '\n', stream);
}
