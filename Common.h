#ifndef COMMON_H
#define COMMON_H

//=============================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//=============================================================================================================

typedef struct String{
    char* string_pointer = nullptr;
    size_t string_lenght = 0;
} String;

typedef struct Onegin{
    char* chars_buffer_ptr = nullptr;
    String* structs_arr    = nullptr;

    size_t chars_number         = 0;
    size_t strings_number       = 0;
    size_t number_of_the_string = 0;

} Onegin;


//=============================================================================================================
/**
 * @brief Counts the number of lines in a source file.
 * 
 * @param Onegin_struct structure pointer
 */
void num_of_strings(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Fills 2 fields of each structure (pointer to buffer part and string length) 
 *        from an array of structures.
 * 
 * @param Onegin_struct structure pointer
 */
void fill_in_structs(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Frees memory.
 * 
 * @param Onegin_struct structure pointer
 */
void destructor(Onegin* Onegin_struct);

//=============================================================================================================

#endif // COMMON_H
