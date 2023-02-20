#ifndef ONEGIN_PROCESSING_H
#define ONEGIN_PROCESSING_H

//=============================================================================================================

#include "InputOutput.h"


#include <stdio.h>
#include <sys/stat.h>

//=============================================================================================================

typedef struct String
{
    char* string_ptr = nullptr;
    size_t string_len = 0;
} String;

typedef struct Onegin
{
    FILE* mainfile      = nullptr;
    char* buffer_ptr    = nullptr; 
    String* structs_arr = nullptr;
    FILE* left_comp     = nullptr;
    FILE* right_comp    = nullptr;

    size_t chars_num   = 0;
    size_t strings_num = 0;

    int error_code = 0;
} Onegin;

//=============================================================================================================
/**
 * @brief Creates and initializes the onegin.
 * 
 * @param onegin structure pointer
 * @param filename the name of the input file
 * @return int 
 */
int onegin_ctor(Onegin* onegin, const char* filename);

//=============================================================================================================
/**
 * @brief Reads the number of characters in the source text from the file input.txt 
 *        using the library <sys/stat.h>.
 * 
 * @param onegin structure pointer
 * @param filename the name of the input file as a parameter 
 * @return int 
 */
int num_of_chars(Onegin* onegin, const char* filename);

//=============================================================================================================
/**
 * @brief Creates a buffer that fills with characters from a file input.txt.
 * 
 * @param onegin structure pointer
 * @param stream file pointer
 * @return int 
 */
int chars_buffer(Onegin* onegin, FILE* stream);

//=============================================================================================================
/**
 * @brief Counts the number of lines in a source file.
 * 
 * @param onegin structure pointer
 * @return int 
 */
void num_of_strings(Onegin* onegin);

//=============================================================================================================
/**
 * @brief Fills 2 fields of each structure (pointer to buffer part and string length) 
 *        from an array of structures.
 * 
 * @param onegin structure pointer
 * @return int 
 */
int fill_in_structs(Onegin* onegin);

//=============================================================================================================
/**
 * @brief Frees memory.
 * 
 * @param onegin structure pointer
 */
void onegin_dtor(Onegin* onegin);

//=============================================================================================================

#endif // ONEGIN_PROCESSING_H
