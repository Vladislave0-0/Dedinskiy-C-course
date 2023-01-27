#ifndef TEXT_SORTING_H
#define TEXT_SORTING_H

//=============================================================================================================

#include "InputOutput.h"
#include "Common.h"

//=============================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>

//=============================================================================================================
/**
 * @brief Outputs text to the terminal that allows you to select the type of sorting.
 * 
 * @param Onegin_struct structure pointer
 */
void sorting_selection(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Comparator for left sorting based on qsort.
 * 
 * @param first_struct 
 * @param second_struct 
 * @return int 
 */
int left_comparator(const void* first_struct, const void* second_struct);

//=============================================================================================================
/**
 * @brief Comparator for right sorting based on qsort.
 * 
 * @param first_struct 
 * @param second_struct 
 * @return int 
 */
int right_comparator(const void* first_struct, const void* second_struct);

//=============================================================================================================
/**
 * @brief Сalls qsort and prints the sorted text to a file "sorted text from left.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void left_sorting(Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Сalls qsort and prints the sorted text to a file "sorted text from right.txt".
 * 
 * @param Onegin_struct structure pointer
 */
void right_sorting(Onegin* Onegin_struct);

//=============================================================================================================

#endif // TEXT_SORTING_H
