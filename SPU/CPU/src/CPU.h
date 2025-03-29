#ifndef CPU_H
#define CPU_H

//=======================================================================================

#include "../../Stack/StackDebug.h"
#include "../../Stack/Stack.h"


#include <math.h>
#include <string.h>
#include <stdlib.h>

//=======================================================================================

const int REGISTER_SHIFT        = 21;
const int RAM_SIZE              = 2304;
const int REGS_NUM              = 4;
const int MAX_WORD_LENGTH       = 32; 
const double CMD_FLOAT_CONSTANT = 1E-6;

//=======================================================================================

#define GETKEY(arg) ((int)arg & 0xFFFF)

//=======================================================================================

struct CPU
{
    Stack* stack   = {};                    //| Pointer to stack structure.
    FILE* bin_file = nullptr;               //| Pointer to binary file.

    int quantity  = 0;                      //| Number of tokens.
    int signature = 0;                      //| Signature.
    int error     = 0;                      //| Error during decoding.
    size_t cur_ip = 0;                      //| Current ip counter.

    elem_t* code_buffer  = nullptr;         //| Pointer to encoded buffer.
    elem_t REG[REGS_NUM] = {0};             //| Array of registers.
    elem_t RAM[RAM_SIZE] = {0};             //| Array of RAM.
};

//=======================================================================================

enum CPU_errors
{
    ERROR_VALUE_OF_ARGC     = 1,            //| Error in the number of command line arguments.
    ERROR_STACK_CREATION    = 2,            //| Stack creation error.   
    ERROR_BIN_FILE_OPEN     = 3,            //| Error opening binary file.
    ERROR_DEVISION_BY_ZERO  = 4,            //| Divide-by-zero error on stack.
    ERROR_NEG_SQRT_ROOT_NUM = 5,            //| Calculating the square root of a negative number.
};

enum CPU_code
{
    // COMMAND
    HLT  = 0,                   //| The end of assembly code reading.
    PUSH = 1,                   //| Push in stack.
    POP  = 2,                   //| Pop from stack.
    ADD  = 3,                   //| Add two numbers in stack.
    SUB  = 4,                   //| Sub two numbers in stack.
    MUL  = 5,                   //| Mul two numbers in stack.
    DIV  = 6,                   //| Div two numbers in stack.
    IN   = 7,                   //| Waiting an integer from console.
    OUT  = 8,                   //| Prints an integer in console.
    RET  = 9,                   //| Returns the ip that comes after CALL.
    POW  = 10,                  //| Raising a number to a power.
    SIN  = 11,                  //| Sine calculation.
    COS  = 12,                  //| Cosine calculation.
    TG   = 13,                  //| Tangent calculation.
    CTG  = 14,                  //| Cotangent calculation.
    SQRT = 15,                  //| Square root calculation.
    NEG  = 16,                  //| Multiply the number in the stack by minus one.
    COPY = 17,                  //| Pushing the last element on the stack.

    REG_DUMP  = 18,             //| Output status of registers.
    RAM_DUMP  = 19,             //| Video memory status output.
    REG_PURGE = 20,             //| Zeroing the state of the registers.

    // REGISTER
    AX = 21,                    //| Register ax.
    BX = 22,                    //| Register bx.
    CX = 23,                    //| Register cx.
    DX = 24,                    //| Register dx.

    // JUMP
    JMP  = 31,                  //| Common jump.
    JE   = 32,                  //| Conditional jump --> label if equal.
    JNE  = 33,                  //| Conditional jump --> label if not equal.
    JG   = 34,                  //| Conditional jump --> label if grower.
    JL   = 35,                  //| Conditional jump --> label if lower.
    CALL = 36,                  //| Jump for functions with stack of returns.
    JGE  = 37,                  //| Conditional jump --> label if grower or equal.
    JLE  = 38,                  //| Conditional jump --> label if lower or equal.
};

enum code_mask
{
    // Example for PUSH:
    // val       === 00000000 00000001 00000000 00000001
    // reg       === 00000000 00000010 00000000 00000001
    // [val]     === 00000000 00000101 00000000 00000001
    // [reg]     === 00000000 00000110 00000000 00000001
    // [val+reg] === 00000000 00000111 00000000 00000001

    // Example for POP:
    // reg       === 00000000 00000010 00000000 00000010
    // [val]     === 00000000 00000101 00000000 00000010
    // [reg]     === 00000000 00000110 00000000 00000010
    // [val+reg] === 00000000 00000111 00000000 00000010

    VAL_MASK = 1 << 16,         //| Bit shift by 16 bits if the argument is a number.
    REG_MASK = 1 << 17,         //| Bit shift by 17 bits if the argument is register.
    RAM_MASK = 1 << 18,         //| Bit shift by 18 bits if the argument is ram.
};

enum TypeOfAsmCode
{
    CMD     = 1,                //| Command.
    VAL     = 2,                //| Value.
    REG     = 3,                //| Register.
    JUMP    = 4,                //| Jump.
    FLAG    = 5,                //| Jump's flag.
    UNKNOWN = 0,                //| Unknown type of the assembler code.
};

// enum for function float_comparison
enum ComparisonResult
{
    UNDER = -1,
    EQUAL =  0,
    OVER  =  1,
};

//=======================================================================================
/**
 * @brief General function of generating and executing code.
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param CPU_filename binary file name.
 * @return int error code.
 */
int CPU_code_ctor(struct CPU* cpu, const char* CPU_filename);

//=======================================================================================
/**
 * @brief Opening a binary file
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param filename file name.
 * @return FILE* pointer on the file.
 */
FILE* open_bin_file(struct CPU* cpu, const char* filename);

//=======================================================================================
/**
 * @brief creating a file with the required extension
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param cpu_file_name binary file name.
 * @return FILE* pointer on the file.
 */
FILE* create_filename(struct CPU* cpu, const char* cpu_file_name);

//=======================================================================================
/**
 * @brief Reading a binary file
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @return int error code.
 */
int reading_file(struct CPU* cpu);

//=======================================================================================
/**
 * @brief Executing binary code.
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param stk structure for stack.
 * @return int error code.
 */
int execute_code(struct CPU* cpu, struct Stack* stk);

//=======================================================================================
/**
 * @brief Getting a pointer to a command argument.
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param arg command argument.
 */
void get_arg(struct CPU* cpu, elem_t** arg);

//=======================================================================================
/**
 * @brief Get a label for the jump argument.
 * 
 * @param cpu a structure for storing all information about the stack and assembly code.
 * @param arg command argument.
 */
void get_label(struct CPU* cpu, elem_t** arg);

//=======================================================================================
/**
 * @brief A function for comparing float numbers with an accuracy of 6 digits 
 *        after the decimal point.
 * 
 * @param x1 first number
 * @param x2 second number
 * @return ComparisonResult 
 */
ComparisonResult float_comparison(const double x1, const double x2);

//=======================================================================================

#endif
