#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

//=============================================================================================================

#include "Common.h"
#include "TextSorting.h"


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

//=============================================================================================================
/**
 * @brief Opens the source file input.txt.
 * 
 * @return FILE* 
 */
FILE* file_open(const char* filename);

//=============================================================================================================
/**
 * @brief Reads the number of characters in the source text from the file input.txt 
 *        using the library <sys/stat.h>.
 * 
 * @param Onegin_struct structure pointer
 * @param filename the name of the input file as a parameter
 */
void num_of_chars(Onegin* Onegin_struct, const char* filename);

//=============================================================================================================
/**
 * @brief Creates a buffer that fills with characters from a file input.txt.
 * 
 * @param Onegin_struct structure pointer
 * @param stream file pointer
 */
void chars_buffer(Onegin* Onegin_struct, FILE* stream);

//=============================================================================================================
/**
 * @brief Integrates the entire process of processing input data.
 * 
 * @param Onegin_struct structure pointer
 * @param filename the name of the input file as a parameter
 */
void input_processing(Onegin* Onegin_struct, const char* filename);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the left edge to the file "sorted text from left.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void left_sort_output(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the right edge to the file "sorted text from right.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void right_sort_output(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Outputs text to the terminal that allows you to select the type of sorting.
 * 
 * @param Onegin_struct structure pointer
 */
void sorting_selection(Onegin* Onegin_struct);

//=============================================================================================================

#endif // INPUT_OUTPUT_H
