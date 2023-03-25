#include "CPU.h"

//=======================================================================================

int main()
{
    struct CPU cpu = {};

    if(CPU_ctor(&cpu) != 0)
    {
        return cpu.error;
    }
}