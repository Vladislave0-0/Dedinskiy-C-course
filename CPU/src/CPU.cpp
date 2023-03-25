#include "CPU.h"
#include <stdlib.h>

//=============================================================================================================

int CPU_ctor(struct CPU* cpu)
{
    struct Stack stk = {};

    if(stack_ctor(&stk) != 0)
    {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_STACK_CREATION);

        cpu->error = ERROR_STACK_CREATION;

        return ERROR_STACK_CREATION;
    }

    cpu->stack = &stk;

   if(open_bin_file(cpu) != 0)
   {
        printf("Error code: %d. Check file \"Stack.h\" to decipher the error code.\n", ERROR_BIN_FILE_OPEN);

        cpu->error = ERROR_BIN_FILE_OPEN;

        return ERROR_BIN_FILE_OPEN;
   }

    reading_file(cpu);

    execute_code(cpu);

    return 0;
}

//=============================================================================================================

int open_bin_file(struct CPU* cpu)
{
    FILE* file_input = fopen("../Assembler/source.code", "rb");

    if(file_input == nullptr)
    {
        cpu->error = ERROR_BIN_FILE_OPEN;

        return ERROR_BIN_FILE_OPEN;
    }

    cpu->bin_file = file_input;

    return 0;
}

//=============================================================================================================

void reading_file(struct CPU* cpu)
{
    elem_t* file_buffer = (elem_t*)calloc(2, sizeof(elem_t));

    fread(file_buffer, sizeof(int), 1, cpu->bin_file);
    fread(file_buffer + 1, sizeof(int), 1, cpu->bin_file);

    cpu->signature = file_buffer[0];
    cpu->quantity = file_buffer[1];

    cpu->code_buffer = (elem_t*)calloc(cpu->quantity, sizeof(elem_t));
    
    for(int i = 2; i < cpu->quantity + 2; i++)
    {
        fread(cpu->code_buffer - 2 + i, sizeof(int), 1, cpu->bin_file);
    }

    // for(int i = 0; i < cpu->quantity; i++)
    // {
    //     printf("[%d] == %d\n", i, cpu->code_buffer[i]);
    // }

    free(file_buffer);
    fclose(cpu->bin_file);
}

//=============================================================================================================

#define DEF_CMD(name, cmd_type, has_arg, cpu_code)          \
    case(name):                                             \
    {                                                       \
        if(has_arg == 1)                                    \
        {                                                   \
            if(cmd_type == CMD)                             \
            {                                               \
                get_arg(cpu, &arg_ptr);                     \
            }                                               \
                                                            \
            else if(cmd_type == JUMP)                       \
            {                                               \
                get_label(cpu, &arg_ptr);                   \
            }                                               \
        }                                                   \
                                                            \
        cpu_code                                            \
                                                            \
        break;                                              \
    }                                                       \

int execute_code(struct CPU* cpu)
{
    // int index = 0;
    int arg = 0;
    int* arg_ptr = &arg;

    int h_val = 0;
    int l_val = 0;

    int* code = cpu->code_buffer;

    while(code[cpu->cur_ip] != HLT)
    {
        // if(index > 10)
        // {
        //     return 0;
        // }

        // printf("cur_ip: %lu\n", cpu->cur_ip);
        // printf("cmd: %d\n\n", code[cpu->cur_ip]);

        switch(GETKEY(code[cpu->cur_ip]))
        {
            #include "../../cmd.h"

            default:
            {
                printf("ПИЗДА РУЛЮ\n");

                break;
            }
        }

        arg = 0;

        arg_ptr = &arg;

        cpu->cur_ip++;
        // index++;
    }

    return 0;
}

#undef DEF_CMD

//=============================================================================================================

void get_arg(struct CPU* cpu, int** arg)
{
    int cmd = cpu->code_buffer[cpu->cur_ip];
    **arg = 0;

    if(cmd & VAL_MASK)
    {
        cpu->cur_ip++;

        **arg += cpu->code_buffer[cpu->cur_ip];
    }

    if(cmd & REG_MASK)
    {
        
        cpu->cur_ip++;

        if(cmd & RAM_MASK)
        {
            **arg += cpu->REG[cpu->code_buffer[cpu->cur_ip] - 21];
        }

        else
        {
            *arg = &cpu->REG[cpu->code_buffer[cpu->cur_ip] - 21];

            return;
        }
    }

    if(cmd & RAM_MASK)
    {
        *arg = &cpu->RAM[**arg];

        return;
    }
}

//=============================================================================================================

void get_label(struct CPU* cpu, int** arg)
{
    cpu->cur_ip++;

    **arg += cpu->code_buffer[cpu->cur_ip];
}