#ifndef CPU_H
#define CPU_H

//=======================================================================================

#include "../../Stack/src/StackDebug.h"
#include "../../Stack/src/Stack.h"

const int REGISTER_SHIFT = 21;
const int RAM_SIZE       = 1000;
const int REGS_NUM       = 4;


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
    ERROR_STACK_CREATION   = 1,
    ERROR_BIN_FILE_OPEN    = 2,
    ERROR_DEVISION_BY_ZERO = 3,
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

int CPU_ctor(struct CPU* cpu);

//=======================================================================================

int open_bin_file(struct CPU* cpu);

//=======================================================================================

void reading_file(struct CPU* cpu);

//=======================================================================================

int execute_code(struct CPU* cpu);

//=======================================================================================

void get_arg(struct CPU* cpu, int** arg);

//=======================================================================================

void get_label(struct CPU* cpu, int** arg);

//=======================================================================================

#endif
