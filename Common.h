#ifndef COMMON_H
#define COMMON_H

//=============================================================================================================

#include "InputOutput.h"


#include <stdio.h>
#include <sys/stat.h>

//=============================================================================================================

typedef struct String{
    char* string_pointer = nullptr;
    size_t string_lenght = 0;
} String;

typedef struct Onegin{
    char* chars_buffer_ptr = nullptr; 
    String* structs_arr    = nullptr;
    FILE* mainfile         = nullptr;

    size_t chars_number         = 0;
    size_t strings_number       = 0;
    size_t number_of_the_string = 0;

    int error_code = 0;
} Onegin;

//=============================================================================================================
/**
 * @brief creates and initializes the Onegin_struct.
 * 
 * @param Onegin_struct structure pointer
 * @param filename the name of the input file as a parameter
 */
int constructor(Onegin* Onegin_struct, const char* filename);

//=============================================================================================================
/**
 * @brief Reads the number of characters in the source text from the file input.txt 
 *        using the library <sys/stat.h>.
 * 
 * @param Onegin_struct structure pointer
 * @param filename the name of the input file as a parameter
 */
int num_of_chars(Onegin* Onegin_struct, const char* filename);

//=============================================================================================================
/**
 * @brief Creates a buffer that fills with characters from a file input.txt.
 * 
 * @param Onegin_struct structure pointer
 * @param stream file pointer
 */
int chars_buffer(Onegin* Onegin_struct, FILE* stream);

//=============================================================================================================
/**
 * @brief Counts the number of lines in a source file.
 * 
 * @param Onegin_struct structure pointer
 */
int num_of_strings(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Fills 2 fields of each structure (pointer to buffer part and string length) 
 *        from an array of structures.
 * 
 * @param Onegin_struct structure pointer
 */
int fill_in_structs(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Frees memory.
 * 
 * @param Onegin_struct structure pointer
 */
void destructor(Onegin* Onegin_struct);

//=============================================================================================================

#endif // COMMON_H
