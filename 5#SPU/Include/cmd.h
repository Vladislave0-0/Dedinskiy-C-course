// CMD
DEF_CMD(HLT, CMD, 0, 
{
    return 0;
})

DEF_CMD(PUSH, CMD, 1, 
{
    PUUSH(*arg_ptr);
})

DEF_CMD(POP, CMD, 1, 
{
    POOP(&h_val);
    *arg_ptr = h_val;
})

DEF_CMD(ADD, CMD, 0, 
{
    POOP(&h_val);
    POOP(&l_val);
    PUUSH(h_val + l_val);
})

DEF_CMD(SUB, CMD, 0, 
{
    POOP(&h_val);
    POOP(&l_val);
    PUUSH(l_val - h_val);
})

DEF_CMD(MUL, CMD, 0, 
{
    POOP(&h_val);
    POOP(&l_val);
    PUUSH(h_val * l_val);
})

DEF_CMD(DIV, CMD, 0, 
{
    POOP(&h_val);
    POOP(&l_val);
    
    if(float_comparison(h_val, 0) == EQUAL)
    {
        cpu->error = ERROR_DEVISION_BY_ZERO;

        return ERROR_DEVISION_BY_ZERO;
    }

    PUUSH(l_val / h_val);
})

DEF_CMD(IN, CMD, 0, 
{
    printf("Enter a number in stack: ");

    scanf(FORM_SPEC, &arg);
    
    PUUSH(arg);
})

DEF_CMD(OUT, CMD, 0,
{
    POOP(&h_val);

    if(float_comparison(h_val, 0) == EQUAL)
    {
        printf("cpu_out: 0\n");
    }

    else
    {
        printf("cpu_out: " FORM_SPEC "\n", h_val);
    }

})

DEF_CMD(RET, CMD, 0, 
{
    POOP(&h_val);
    
    cpu->cur_ip = (size_t)h_val - 1;
})

// JMP
DEF_CMD(JMP, JUMP, 1, 
{
    cpu->cur_ip = (size_t)*arg_ptr - 1;
})

DEF_CMD(JE, JUMP, 1,
{
    POOP(&h_val);
    POOP(&l_val);
    
    if(float_comparison(l_val, h_val) == EQUAL)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }
})

DEF_CMD(JNE, JUMP, 1, 
{
    POOP(&h_val);
    POOP(&l_val);

    if(float_comparison(l_val, h_val) != EQUAL)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }  
})

DEF_CMD(JG, JUMP, 1, 
{
    POOP(&h_val);
    POOP(&l_val);

    if(float_comparison(l_val, h_val) == OVER)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }  
})

DEF_CMD(JGE, JUMP, 1,
{
    POOP(&h_val);
    POOP(&l_val);
    
    if(float_comparison(l_val, h_val) != UNDER)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }
})

DEF_CMD(JLE, JUMP, 1, 
{
    POOP(&h_val);
    POOP(&l_val);

    if(float_comparison(l_val, h_val) != OVER)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }
})

DEF_CMD(JL, JUMP, 1, 
{
    POOP(&h_val);
    POOP(&l_val);

    if(float_comparison(l_val, h_val) == UNDER)
    {
        cpu->cur_ip = (size_t)*arg_ptr - 1;
    }  
})

DEF_CMD(CALL, JUMP, 1, 
{
    PUUSH((elem_t)(cpu->cur_ip + 1));

    cpu->cur_ip = (size_t)*arg_ptr - 1;
})


DEF_CMD(POW, CMD, 0, 
{
    POOP(&h_val);
    POOP(&l_val);

    PUUSH((elem_t)pow(l_val, h_val));
})

DEF_CMD(SIN, CMD, 0, 
{
    POOP(&h_val);

    PUUSH((elem_t)sin(h_val));
})

DEF_CMD(COS, CMD, 0, 
{
    POOP(&h_val);

    PUUSH((elem_t)cos(h_val));
})

DEF_CMD(TG, CMD, 0, 
{
    POOP(&h_val);

    PUUSH((elem_t)tan(h_val));
})

DEF_CMD(CTG, CMD, 0, 
{
    POOP(&h_val);

    PUUSH((elem_t)(1 / tan(h_val)));
})

DEF_CMD(SQRT, CMD, 0,
{
    POOP(&h_val);

    if(float_comparison(l_val, 0) == UNDER)
    {
        cpu->error = ERROR_NEG_SQRT_ROOT_NUM;

        return ERROR_NEG_SQRT_ROOT_NUM;
    }

    PUUSH((elem_t)sqrt(h_val));
})

DEF_CMD(NEG, CMD, 0,
{
    POOP(&h_val);

    PUUSH(-1 * h_val);
})

DEF_CMD(REG_DUMP, CMD, 0,
{
    printf("REG_DUMP:\n");
    printf("[" FORM_SPEC ", " FORM_SPEC ", " FORM_SPEC ", " FORM_SPEC "]\n", RAX, RBX, RCX, RDX);
})

DEF_CMD(REG_PURGE, CMD, 0,
{
    for(int i = 0; i < REGS_NUM; i++)
    {
        CREG[i] = 0;
    }
})

DEF_CMD(RAM_DUMP, CMD, 0,
{
    int koef = 1;

    printf("RAM_DUMP:\n");

    for(int m = 0, n = 1; m < RAM_SIZE; m++, n++)
    {
        if(float_comparison(CRAM[m], 0) == EQUAL)
        {
            printf("□ ");
        }

        else
        {
            printf("■ ");
        }

        if(n == koef * (int)sqrt(RAM_SIZE))
        {
            printf("\n");

            koef++;
        }
    }
})

DEF_CMD(COPY, CMD, 0, 
{
    POOP(&h_val);
    PUUSH(h_val);
    PUUSH(h_val);
})
