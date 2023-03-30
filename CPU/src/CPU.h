#ifndef CPU_H
#define CPU_H

//=======================================================================================

#include "../../Stack/StackDebug.h"
#include "../../Stack/Stack.h"


#include <math.h>
#include <string.h>
#include <stdlib.h>

//=======================================================================================

const int REGISTER_SHIFT  = 21;
const int RAM_SIZE        = 2304;
const int REGS_NUM        = 4;
const int MAX_WORD_LENGTH = 32; 

//=======================================================================================

#define GETKEY(arg) (arg & 0xFFFF)

//=======================================================================================

struct CPU
{
    Stack* stack   = {};
    FILE* bin_file = nullptr;

    int quantity  = 0;
    int signature = 0;
    int error     = 0;
    size_t cur_ip = 0;

    elem_t* code_buffer  = nullptr;
    elem_t REG[REGS_NUM] = {0};
    elem_t RAM[RAM_SIZE] = {0};
};

//=======================================================================================

enum CPU_errors
{
    ERROR_VALUE_OF_ARGC     = 1,
    ERROR_STACK_CREATION    = 2,
    ERROR_BIN_FILE_OPEN     = 3,
    ERROR_DEVISION_BY_ZERO  = 4,
    ERROR_NEG_SQRT_ROOT_NUM = 5,
};

enum CPU_code_mask
{
    HLT  = 0,
    PUSH = 1,
    POP  = 2,
    ADD  = 3,
    SUB  = 4,
    MUL  = 5,
    DIV  = 6,
    IN   = 7,
    OUT  = 8,
    RET  = 9,
    POW  = 10,
    SIN  = 11,
    COS  = 12,
    TG   = 13,
    CTG  = 14,
    SQRT = 15,
    NEG  = 16,
    COPY = 17,
    
    REG_DUMP  = 18,
    RAM_DUMP  = 19,
    REG_PURGE = 20,

    AX = 21,
    BX = 22,
    CX = 23,
    DX = 24,

    JMP  = 31,
    JE   = 32,
    JNE  = 33,
    JG   = 34,
    JL   = 35,
    CALL = 36,
    JGE  = 37,
    JLE  = 38,
};

enum CMD_mask
{
    VAL_MASK = 1 << 16,
    REG_MASK = 1 << 17,
    RAM_MASK = 1 << 18,
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

//=======================================================================================

int CPU_code_ctor(struct CPU* cpu, const char* CPU_filename);

//=======================================================================================

FILE* open_bin_file(struct CPU* cpu, const char* filename);

//=======================================================================================

FILE* create_filename(struct CPU* cpu, const char* cpu_file_name);

//=======================================================================================

int reading_file(struct CPU* cpu);

//=======================================================================================

int execute_code(struct CPU* cpu, struct Stack* stk);

//=======================================================================================

void get_arg(struct CPU* cpu, elem_t** arg);

//=======================================================================================

void get_label(struct CPU* cpu, int** arg);

//=======================================================================================

#endif
