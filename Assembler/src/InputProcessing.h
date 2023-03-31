#ifndef INPUT_PROCESSING_H
#define INPUT_PROCESSING_H

//================================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

//================================================================================================

const int WORD_LENGTH = 32;

//================================================================================================

struct FlagsToken
{
    char text[WORD_LENGTH] = {0};           //| Label's or flag's text after word splitting.
    size_t ip = 0;                          //| Ip of this label or flag.
};

struct FlagsInfo
{
    FlagsToken* flags_arr = nullptr;        //| Array of pointers on all flags.
    size_t cur_flag       = 0;              //| Counter for current flag.
    size_t flags_num      = 0;              //| Total number of flags.

    FlagsToken* jumps_arr = nullptr;        //| Array of pointers on all jumps.
    size_t cur_jump       = 0;              //| Counter for current jump.
    size_t jumps_num      = 0;              //| Total number of jumps.
};

struct TextInfo
{
    char asm_file_name[WORD_LENGTH] = {0};      //| Assembler file name.

    FILE* mainfile         = nullptr;           //| Assembler file pointer.
    char* chars_buffer_ptr = nullptr;           //| Pointer to a buffer that holds all the text.
    char** ptr_arr         = nullptr;           //| An array of pointers to each word in the text.

    size_t chars_number = 0;                    //| The total number of characters in the text.
    size_t words_num    = 0;                    //| The total number of words in the text.
    size_t cur_word     = 0;                    //| Counter for current word.
    size_t tok_num      = 0;                    //| The total number of tokens.

    int error = 0;                              //| Error code.
};

//================================================================================================

enum InputProcessingErrors
{
    ERROR_VALUE_OF_ARGC      = 1,           //| Error in the number of command line arguments.
    ERROR_MAIN_FILE_OPEN     = 2,           //| Assembly file opening error.
    ERROR_EMPTY_MAIN_FILE    = 3,           //| Assembler file is empty.
    ERROR_LEXICAL_PROCESSING = 4,           //| Error in lexical text processing.
    ERROR_FLAGS_NUM          = 5,           //| Incorrect quantity of flags.
    ERROR_DOUBLE_FLAGS       = 6,           //| Double labels.
    ERROR_JUMP_WITHOUT_FLAG  = 7,           //| Jump has no argument.
    ERROR_UNKNOWN_JUMP_FLAG  = 8,           //| Jump points to non-existent label.
    ERROR_FLAGS_CALLOC_NULL  = 9,           //| FLags array creation error.
    ERROR_JUMPS_CALLOC_NULL  = 10,          //| Jumps array creation error.
};

//================================================================================================
/**
 * @brief Lexical and syntactic processing of the assembler file. Creating and splitting text into 
 *        separate constructs.
 * 
 * @param TextInfo structure for lexical processing.
 * @param Flags structure for handling flags, jumps and labels.
 * @param filename file name.
 */
void text_info_ctor(struct TextInfo* TextInfo, struct FlagsInfo* Flags, const char* filename);

//================================================================================================
/**
 * @brief Opening a file by its name.
 * 
 * @param TextInfo structure for lexical processing.
 * @param filename file name.
 */
void open_file(struct TextInfo* TextInfo, const char* filename);

//================================================================================================
/**
 * @brief Counting the number of characters in a text.
 * 
 * @param TextInfo structure for lexical processing.
 * @param filename file name.
 */
void num_of_chars(struct TextInfo* TextInfo, const char* filename);

//================================================================================================
/**
 * @brief Creating and filling an array with assembler text.
 * 
 * @param TextInfo structure for lexical processing.
 */
void chars_buffer(struct TextInfo* TextInfo);

//================================================================================================
/**
 * @brief Word count.
 * 
 * @param TextInfo structure for lexical processing.
 */
void count_words(struct TextInfo* TextInfo);

//================================================================================================
/**
 * @brief Filling an array of structures.
 * 
 * @param TextInfo structure for lexical processing.
 */
void fill_ptr_arr(struct TextInfo* TextInfo);

//================================================================================================
/**
 * @brief Lexical processing of assembly text.
 * 
 * @param TextInfo structure for lexical processing.
 * @param Flags structure for handling flags, jumps and labels.
 */
void lexical_processing(struct TextInfo* TextInfo, struct FlagsInfo* Flags);

//================================================================================================
/**
 * @brief Parsing labels, jumps and flags.
 * 
 * @param TextInfo structure for lexical processing.
 * @param Flags structure for handling flags, jumps and labels.
 */
void flags_processing(struct TextInfo* TextInfo, struct FlagsInfo* Flags);

//================================================================================================
/**
 * @brief Function to free occupied memory.
 * 
 * @param TextInfo structure for lexical processing.
 * @param Flags structure for handling flags, jumps and labels.
 */
void TextInfo_dtor(struct TextInfo* TextInfo, struct FlagsInfo* Flags);

//================================================================================================

#endif //INPUT_PROCESSING_H
