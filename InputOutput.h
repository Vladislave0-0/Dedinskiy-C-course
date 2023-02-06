#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

//=============================================================================================================

#include "Common.h"
#include "TextSorting.h"
#include "OneginDebug.h"


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
void open_file(Onegin* Onegin_struct, const char* filename);

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
 * @brief After the sorted text outputs the original text to the same file.
 * 
 * @param Onegin_struct structure pointer
 * @param stream file pointer
 */
void output_source_text(Onegin* Onegin_struct, FILE* stream);

//=============================================================================================================
/**
 * @brief Outputs text to the terminal that allows you to select the type of sorting.
 * 
 * @param Onegin_struct structure pointer
 */
void sorting_selection(Onegin* Onegin_struct);

//=============================================================================================================

#endif // INPUT_OUTPUT_H
