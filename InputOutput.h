#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

//=============================================================================================================

#include "Common.h"
#include "TextSorting.h"

//=============================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
//=============================================================================================================
/**
 * @brief Opens the source file input.txt.
 * 
 * @return FILE* 
 */
FILE* file_open();

//=============================================================================================================
/**
 * @brief Reads the number of characters in the source text from the file input.txt.
 * 
 * @param Onegin_struct structure pointer
 * @param stream file pointer
 */
void num_of_chars(Onegin* Onegin_struct, FILE* stream);

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
 */
void input_processing  (Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the left edge to the file "sorted text from left.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void left_sort_output  (Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the right edge to the file "sorted text from right.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void right_sort_output (Onegin* Onegin_struct);

//=============================================================================================================

#endif // INPUT_OUTPUT_H
