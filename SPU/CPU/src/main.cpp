#include "CPU.h"

//=======================================================================================

int main(int argc, char *argv[])
{
    if((argc == 1) && (strcmp(argv[0], "./CPU") == 0))
    {
        printf("\nCPU: You didn't write a file name on the command line. The default file is \"source.code\".\n\n");
    }

    else if(argc != 2)
    {
        printf("Incorrect value of the number of command line arguments!\n");

        return ERROR_VALUE_OF_ARGC;
    }

    struct CPU cpu = {};

    if(argc == 1)
    {
        CPU_code_ctor(&cpu, "source.code");
    }

    else if(argc == 2)
    {
        CPU_code_ctor(&cpu, argv[1]);
    }

    // fclose();

    // if(CPU_ctor(&cpu) != 0)
    // {
    //     return cpu.error;
    // }
}
