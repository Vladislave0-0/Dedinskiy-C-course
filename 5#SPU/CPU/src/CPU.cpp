#include "CPU.h"
#include "../../Include/DSL.h"

//=============================================================================================================

int CPU_code_ctor(struct CPU* cpu, const char* cpu_file_name)
{
    struct Stack stk = {};

    if(stack_ctor(&stk) != 0)
    {
        printf("IN CPU. Error code: %d. Check file \"CPU.h\" to decipher the error code.\n", ERROR_STACK_CREATION);

        cpu->error = ERROR_STACK_CREATION;

        return ERROR_STACK_CREATION;
    }

    cpu->stack = &stk;

    cpu->bin_file = create_filename(cpu, cpu_file_name);

    if(cpu->bin_file == nullptr)
    {
        printf("IN CPU. Error code: %d. Check file \"CPU.h\" to decipher the error code.\n", ERROR_BIN_FILE_OPEN);

        cpu->error = ERROR_BIN_FILE_OPEN;

        return ERROR_BIN_FILE_OPEN;
    }

    if(reading_file(cpu) != 0)
    {
        printf("IN CPU. Error code: %d. Check file \"CPU.h\" to decipher the error code.\n", cpu->error);

        return cpu->error;
    }

    if(execute_code(cpu, &stk) != 0)
    {
        printf("IN CPU. Error code: %d. Check file \"CPU.h\" to decipher the error code.\n", cpu->error);

        return cpu->error;
    }

    fclose(stk.log_file);


    return 0;
}

//=============================================================================================================

FILE* open_bin_file(struct CPU* cpu, const char* filename)
{
    FILE* file_input = fopen(filename, "rb");

    if(file_input == nullptr)
    {
        printf("IN CPU. There is no file named \"%s\".\n", filename);

        cpu->error = ERROR_BIN_FILE_OPEN;

        return file_input;
    }

    return file_input;
}

//=============================================================================================================

FILE* create_filename(struct CPU* cpu, const char* cpu_file_name)
{
    char new_file[MAX_WORD_LENGTH] = "../Assembler/";

    strcat(new_file, cpu_file_name);

    FILE* file_input = open_bin_file(cpu, new_file);

    return file_input; 
}

//=============================================================================================================

int reading_file(struct CPU* cpu)
{
    elem_t* file_buffer = (elem_t*)calloc(2, sizeof(elem_t));

    if(file_buffer == nullptr)
    {
        return ERROR_VALUE_OF_ARGC;
    }

    fread(file_buffer, sizeof(elem_t), 1, cpu->bin_file);
    fread(file_buffer + 1, sizeof(elem_t), 1, cpu->bin_file);

    cpu->signature = (int)file_buffer[0];
    cpu->quantity  = (int)file_buffer[1];

    // printf("%d\n", cpu->signature);
    // printf("%d\n", cpu->quantity);

    cpu->code_buffer = (elem_t*)calloc(cpu->quantity, sizeof(elem_t));
    
    for(int i = 2; i < cpu->quantity + 2; i++)
    {
        fread(cpu->code_buffer - 2 + i, sizeof(int), 1, cpu->bin_file);
    }

    // for(int i = 0; i < cpu->quantity; i++)
    // {
    //     printf("[%d] == " FORM_SPEC "\n", i, cpu->code_buffer[i]);
    // }

    free(file_buffer);
    fclose(cpu->bin_file);

    return 0;
}

//=============================================================================================================

#define DEF_CMD(name, cmd_type, has_arg, cpu_code)          \
    case(name):                                             \
    {                                                       \
        PRINT_LOG("COMMAND: %s\n", #name);                  \
                                                            \
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

int execute_code(struct CPU* cpu, struct Stack* stk)
{
    
    elem_t  arg     = 0;
    elem_t* arg_ptr = &arg;

    elem_t h_val = 0;
    elem_t l_val = 0;

    elem_t* code = cpu->code_buffer;

    while(float_comparison(code[cpu->cur_ip], HLT) != EQUAL)
    {
        switch(GETKEY(code[cpu->cur_ip]))
        {
            #include "../../Include/cmd.h"

            default:
            {
                printf("SOMETHING WRONG IN EXECUTE_CODE!\n");

                break;
            }
        }

        arg = 0;

        arg_ptr = &arg;

        cpu->cur_ip++;

        stk_print_log(stk);
        PRINT_LOG("REG: [" FORM_SPEC "; " FORM_SPEC "; " FORM_SPEC "; " FORM_SPEC "]\n\n\n", RAX, RBX, RCX, RDX);
    }

    return 0;
}

#undef DEF_CMD

//=============================================================================================================

void get_arg(struct CPU* cpu, elem_t** arg)
{
    int cmd = (int)cpu->code_buffer[cpu->cur_ip];
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
            **arg += cpu->REG[(int)cpu->code_buffer[cpu->cur_ip] - REGISTER_SHIFT];
        }

        else
        {
            *arg = &cpu->REG[(int)cpu->code_buffer[cpu->cur_ip] - REGISTER_SHIFT];

            return;
        }
    }

    if(cmd & RAM_MASK)
    {
        *arg = &cpu->RAM[(int)**arg];

        return;
    }
}

//=============================================================================================================

void get_label(struct CPU* cpu, elem_t** arg)
{
    cpu->cur_ip++;

    **arg += cpu->code_buffer[cpu->cur_ip];
}

//=============================================================================================================

ComparisonResult float_comparison(const double x1, const double x2)
{
    if (fabs(x1 - x2) <= CMD_FLOAT_CONSTANT)
    {
        return EQUAL;
    }

    else 
    {
        return ((x1-x2) > CMD_FLOAT_CONSTANT) ? OVER : UNDER;
    }
}
