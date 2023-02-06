#ifndef ONEGIN_DEBUG_H
#define ONEGIN_DEBUG_H

//======================================================================================================================

#include "InputOutput.h"

//======================================================================================================================

#define ERROR_PRINT(...) fprintf(ERROR_FILE, __VA_ARGS__)

#define ONEGIN_DUMP(onegin_struct) onegin_dump(onegin_struct, __FILE__, __LINE__, __PRETTY_FUNCTION__)

#define DBG() printf("DBG_OUT %s %d at %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__)

//======================================================================================================================

#define ASSERT_OK(Onegin_struct)                         \
    do                                                   \
    {                                                    \
        if(onegin_verify(Onegin_struct) != 0)            \
        {                                                \
            ONEGIN_DUMP(Onegin_struct);                  \
            assert_dtor(Onegin_struct);                  \
            close_errors_file();                         \
        }                                                \
    } while(0)                                           \

//======================================================================================================================
/**
 * @brief Notes the type of error in Onegin_struct.
 * 
 */
enum OneginErrors
{
    ERROR_OPEN_MAINFILE          = 1 << 0,    // Onegin_struct->mainfile == nullptr 
    ERROR_CHARS_NUM_BELOW_NULL   = 1 << 1,    // Onegin_struct->chars_number <= 0
    ERROR_BUFFER_NULLPTR         = 1 << 2,    // Onegin_struct->chars_buffer_ptr == nullptr
    ERROR_STRINGS_NUM_BELOW_NULL = 1 << 3,    // Onegin_struct->strings_number <= 0
    ERROR_STRUCTS_ARR_NULLPTR    = 1 << 4,    // Onegin_struct->structs_arr == nullptr
};

//======================================================================================================================
/**
 * @brief Prints the error data to the file onegin_errors.txt.
 * 
 * @param Onegin_struct the Onegin_struct pointer
 * @param file_name the name of the file that contains the function
 * @param line line number where the error was found
 * @param function_name the name of the function in which the error was found
 */
void onegin_dump(struct Onegin* Onegin_struct, const char* file_name, unsigned long line, const char* function_name);

//======================================================================================================================
/**
 * @brief Сonsiders the error code as the sum of errors in binary code.
 * 
 * @param Onegin_struct structure pointer
 * @return int 
 */
int onegin_verify(struct Onegin* Onegin_struct);

//======================================================================================================================
/**
 * @brief Decodes the error and prints the name of the error to the file.
 * 
 * @param Onegin_struct structure pointer
 */
void onegin_error_decoder(struct Onegin* Onegin_struct);

//======================================================================================================================
/**
 * @brief If an error was found in the middle of running the program, this function removes 
 *        the Onegin_struct, fills Onegin_struct->String fields with 0 value, frees memory.
 * 
 * @param Onegin_struct structure pointer
 */
void assert_dtor(struct Onegin* Onegin_struct);

//======================================================================================================================
/**
 * @brief Opens the file onegin_errors.txt in mode "w".
 * 
 */
void open_errors_file();

//======================================================================================================================
/**
 * @brief Closes the file onegin_errors.txt.
 * 
 */
void close_errors_file();

//======================================================================================================================

#endif // ONEGIN_DEBUG_H
