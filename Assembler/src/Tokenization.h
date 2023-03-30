#ifndef TOKENIZATION_H
#define TOKENIZATION_H
//=============================================================================================================

#include "InputProcessing.h"

//=============================================================================================================

const int MAX_WORD_LENGTH = 32;

//=============================================================================================================

struct Tokens
{
    char text[MAX_WORD_LENGTH] = {0};         //| Token represented as text.

    size_t tok_type = 0;                      //| Token type.
    int asm_code    = 0;                      //| Token represented as ASM code.
    int value       = 0;                      //| Value for tokens with type VAL.

    int error = 0;                            //| Error during tokenization.
};

struct AsmInfo 
{
    FILE* asm_file = nullptr;                 //| File with assembler listing.
    FILE* bin_file = nullptr;                 //| File with signature, quantity, assembler codes for CPU.
    FILE* lst_file = nullptr;                 //| File with convenient output of assembler code after tokenization.

    char signature[4] = "HUI";                //| The signature of assembler.
    size_t quantity   = 0;                    //| Number of tokens.

    Tokens* tok_arr = nullptr;                //| Array of token structures.
    int* code       = nullptr;                //| Array with assembler codes.
    size_t cur_ip   = 0;                      //| Current ip counter.

    size_t error = 0;                         //| Is equal 0, if there were no errors in tokenization.
};

//=============================================================================================================

enum AssemblerCodes
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
    COPY = 17,                  //| 

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

enum TypeOfAsmCode
{
    CMD     = 1,                //| Command.
    VAL     = 2,                //| Value.
    REG     = 3,                //| Register.
    JUMP    = 4,                //| Jump.
    FLAG    = 5,                //| Jump's flag.
    UNKNOWN = 0,                //| Unknown type of the assembler code.
};

enum CodeMask
{
    // Example for PUSH:
    // val       == 00000000 00000001 00000000 00000001
    // reg       == 00000000 00000010 00000000 00000001
    // [val]     == 00000000 00000101 00000000 00000001
    // [reg]     == 00000000 00000110 00000000 00000001
    // [val+reg] == 00000000 00000111 00000000 00000001

    // Example for POP:
    // reg       == 00000000 00000010 00000000 00000010
    // [val]     == 00000000 00000101 00000000 00000010
    // [reg]     == 00000000 00000110 00000000 00000010
    // [val+reg] == 00000000 00000111 00000000 00000010

    VAL_MASK = 1 << 16,         //| Bit shift by 16 bits if the argument is a number.
    REG_MASK = 1 << 17,         //| Bit shift by 17 bits if the argument is register.
    RAM_MASK = 1 << 18,         //| Bit shift by 18 bits if the argument is ram.
};

enum AssemblerErrors
{
    ERROR_TOKENIZATION    = 1,    //| If at least one token has an error.
    ERROR_TOKEN           = 2,    //| Unknown token.
    CMD_WITH_ERROR_ARG    = 3,    //| Command with invalid argument.
    ARG_WITH_ERROR_CMD    = 4,    //| Argument with invalid command.
    ERROR_HLT_NUM         = 5,    //| Incorrect value of code endings for the processor.
    ERROR_LST_FILE_OPEN   = 6,    //| 
    ERROR_TOK_ARR_CALLOC  = 7,
    ERROR_CODE_ARR_CALLOC = 8,
};

//=============================================================================================================

void AsmInfo_ctor(struct AsmInfo* AsmInfo, struct TextInfo* TextInfo, struct FlagsInfo* Flags);

//=============================================================================================================

FILE* open_file(const char* filename);

//=============================================================================================================

FILE* create_file(char* asm_file_name, const char* extension);

//=============================================================================================================

void listing(struct AsmInfo* AsmInfo);

//=============================================================================================================

void tokens_processing(struct AsmInfo* AsmInfo, struct TextInfo* TextInfo, struct FlagsInfo* Flags);

//=============================================================================================================

void HLT_processing(struct AsmInfo* AsmInfo);

//=============================================================================================================

void args_processing(struct AsmInfo* AsmInfo, struct TextInfo* TextInfo, struct FlagsInfo* Flags, int AsmCode);

//=============================================================================================================

int get_signature(AsmInfo* AsmInfo);

//=============================================================================================================

void bin_file_code(struct AsmInfo* AsmInfo, struct TextInfo* TextInfo);

//=============================================================================================================

void AsmInfo_dtor(struct AsmInfo* AsmInfo);

//=============================================================================================================

#endif // TOKENIZATION_H
