#include "InputProcessing.h"
#include "Tokenization.h"

//===============================================================================================================

int main(int argc, char *argv[])
{
    if((argc == 1) && (strcmp(argv[0], "./asm") == 0))
    {
        printf("\nIN ASM. You didn't write a file name on the command line. The default file is \"source.txt\".\n\n");
    }

    else if(argc != 2)
    {
        printf("IN ASM. Incorrect value of the number of command line arguments!\n");

        return ERROR_VALUE_OF_ARGC;
    }

    struct TextInfo TextInfo = {};
    struct FlagsInfo Flags   = {};
    struct AsmInfo AsmInfo   = {};

    if(argc == 1)
    {
        text_info_ctor(&TextInfo, &Flags, "source.txt");
    }

    else if(argc == 2)
    {
        text_info_ctor(&TextInfo, &Flags, argv[1]);
    }
    
    if(TextInfo.error != 0)
    {
        TextInfo_dtor(&TextInfo, &Flags);

        return TextInfo.error;
    }


    AsmInfo_ctor(&AsmInfo, &TextInfo, &Flags);

    if(AsmInfo.error != 0)
    {
        TextInfo_dtor(&TextInfo, &Flags);

        fclose(AsmInfo.lst_file);
        free(AsmInfo.tok_arr);
        free(AsmInfo.code);

        return -1;
    }

    // printf("code:\n");
    // for(size_t i = 0; i < AsmInfo.quantity; i++)
    // {
    //     printf("%d ", AsmInfo.code[i]);
    // }
    // printf("\n");

    TextInfo_dtor(&TextInfo, &Flags);
    AsmInfo_dtor(&AsmInfo);
}
