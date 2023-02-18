#ifndef TEXT_SORTING_H
#define TEXT_SORTING_H

//=============================================================================================================

#include "InputOutput.h"


#include <string.h>
#include <ctype.h>

//=============================================================================================================
/**
 * @brief Comparator for left sorting based on qsort.
 * 
 * @param first_struct pointer to a first structure from an array of structures that store a pointer 
 *                     to a part of the buffer and the length of the string
 * @param second_struct pointer to a second structure from an array of structures that store a pointer 
 *                      to a part of the buffer and the length of the string
 * @return int 
 */
int left_comparator(const void* first_struct, const void* second_struct);

//=============================================================================================================
/**
 * @brief Comparator for right sorting based on qsort.
 * 
 * @param first_struct pointer to a first structure from an array of structures that store a pointer 
 *                     to a part of the buffer and the length of the string
 * @param second_struct pointer to a second structure from an array of structures that store a pointer 
 *                      to a part of the buffer and the length of the string
 * @return int 
 */
int right_comparator(const void* first_struct, const void* second_struct);

//=============================================================================================================
/**
 * @brief Сalls qsort and prints the sorted text to a file "sorted text from left.txt".
 * 
 * @param Onegin_struct structure pointer
 * @return int 
 */
int left_sorting(struct Onegin* Onegin_struct);

//=============================================================================================================
/**
 * @brief Сalls qsort and prints the sorted text to a file "sorted text from right.txt".
 * 
 * @param Onegin_struct structure pointer
 * @return int 
 */
int right_sorting(struct Onegin* Onegin_struct);

//=============================================================================================================

#endif // TEXT_SORTING_H
