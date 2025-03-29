#ifndef STRING_FUNCTIONS_H
#define STRING_FUNCTIONS_H

//==============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

//==============================================================================
/**
 * @brief Returns the length of the string with the null terminator 
 *        as a character of the string.
 * 
 * @return size_t 
 */
size_t my_strlen(const char* str);

//==============================================================================
/**
 * @brief Appends the newline character to the output.
 * 
 * @return size_t 
 */
size_t my_puts(const char* str);

//==============================================================================
/**
 * @brief Returns pointer to the found character in str, or null pointer 
 *        if no such character is found.
 * 
 * @return char* 
 */
char* my_strchr(char* str, char chr);

//==============================================================================
/**
 * @brief Returns a copy of src.
 * 
 * @return char* 
 */
char* my_strcpy(char* dest, const char* src);

//==============================================================================
/**
 * @brief Returns a copy of src up to some character n.
 * 
 * @return char* 
 */
char* my_strncpy(char* dest, const char* src, size_t n);

//==============================================================================
/**
 * @brief Appends to the string pointed to by the destination argument 
 *        the string pointed to by the append argument.
 * 
 * @return char* 
 */
char* my_strcat(char* dest, const char* append);

//==============================================================================
/**
 * @brief Appends to the string pointed to by the destination argument 
 *        the string pointed to by the append argument up to some character n.
 * 
 * @return char* 
 */
char* my_strncat(char* dest, const char* append, size_t n);

//==============================================================================
/**
 * @brief Duplication of a line with allocation of memory for a new line.
 * 
 * @return char* 
 */
char* my_strdup(char* src);

//==============================================================================
/**
 * @brief In case of successful reading of the line, a pointer to the array is 
 *        returned, in which the read data is placed.
 * 
 * @return const char* 
 */
const char* my_fgets(FILE* stream, size_t size_of_dest, char* dest);

//==============================================================================
/**
 * @brief Reads characters from the input stream up to a character delim or EOF 
 *        and puts them into a string.
 * 
 * @return size_t 
 */
ssize_t my_getdelim(char **lineptr, size_t *n, int delim, FILE* stream);

//==============================================================================
/**
 * @brief Reads characters from the input stream up to a character '\n' or EOF 
 *        and puts them into a string. It is a special case of the function
 *        my_getdelim.
 * 
 * @return size_t 
 */
ssize_t my_getline(char **lineptr, size_t *n, FILE *stream) ;

//==============================================================================

#endif // STRING_FUNCTIONS_H
