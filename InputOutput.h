#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

//=============================================================================================================

#include "OneginProcessing.h"
#include "TextSorting.h"


#include <stdio.h>
#include <stdlib.h>

//=============================================================================================================
/**
 * @brief Notes the code of error in stack.
 * 
 */
enum ErrorCodes
{
    ERROR_OPEN_MAINFILE            = 1,      //| File creation error.
    ERROR_FSTAT_SIZE               = 2,      //| Error counting characters from file.
    ERROR_BUFFER_NULLPTR           = 3,      //| Buffer creation error.
    ERROR_FREAD                    = 4,      //| Error counting strings from buffer.
    ERROR_STRUCTS_ARR_NULLPTR      = 5,      //| Structs array creation error.
    ERROR_LEFT_COMPARATOR_NULLPTR  = 6,      //| File for left sotring creation error.
    ERROR_RIGHT_COMPARATOR_NULLPTR = 7,      //| File for right sotring creation error.
    ERROR_SORTING_TYPE             = 8,      //| Error when user select sort.
};

//=============================================================================================================
/**
 * @brief Opens the source file input.txt.
 * 
 * @param onegin structure pointer
 * @param filename the name of the input file
 * @return int 
 */
int open_file(Onegin* onegin, const char* filename);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the left edge to the file "sorted text from left.txt".
 * 
 * @param onegin structure pointer
 * @return int 
 */
int left_sort_output(Onegin* onegin);

//=============================================================================================================
/**
 * @brief Outputs the sorted text from the right edge to the file "sorted text from right.txt".
 * 
 * @param onegin structure pointer
 * @return int 
 */
int right_sort_output(Onegin* onegin);

//=============================================================================================================
/**
 * @brief After the sorted text outputs the original text to the same file.
 * 
 * @param onegin structure pointer
 * @param stream file pointer
 */
void output_source_text(Onegin* onegin, FILE* stream);

//=============================================================================================================
/**
 * @brief Outputs text to the terminal that allows you to select the type of sorting.
 * 
 * @param onegin structure pointer
 * @return int 
 */
int sorting_selection(Onegin* onegin);

//=============================================================================================================

#endif // INPUT_OUTPUT_H
