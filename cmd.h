// CMD
DEF_CMD(HLT, CMD, 0, 
{
    return 0;
})

DEF_CMD(PUSH, CMD, 1, 
{
    stack_push(cpu->stack, *arg_ptr);
})

DEF_CMD(POP, CMD, 1, 
{
    stack_pop(cpu->stack, &h_val);
    *arg_ptr = h_val;
})

DEF_CMD(ADD, CMD, 0, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);
    stack_push(cpu->stack, h_val + l_val);
})

DEF_CMD(SUB, CMD, 0, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);
    stack_push(cpu->stack, l_val - h_val);
})

DEF_CMD(MUL, CMD, 0, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);
    stack_push(cpu->stack, h_val*l_val);
})

DEF_CMD(DIV, CMD, 0, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);

    if(h_val == 0)
    {
        return ERROR_DEVISION_BY_ZERO;
    }

    stack_push(cpu->stack, l_val/h_val);
})

DEF_CMD(IN, CMD, 0, 
{
    printf("Enter a number in stack: ");

    scanf("%d", &arg);
    
    stack_push(cpu->stack, arg);
})

DEF_CMD(OUT, CMD, 0,
{
    stack_pop(cpu->stack, &h_val);

    printf("cpu_out: %d\n", h_val);
})

DEF_CMD(RET, CMD, 0, 
{
    stack_pop(cpu->stack, &h_val);
    
    cpu->cur_ip = h_val - 1;
})

// JMP
DEF_CMD(JMP, JUMP, 1, 
{
    cpu->cur_ip = *arg_ptr - 1;
})

DEF_CMD(JE, JUMP, 1,
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);

    if(l_val == h_val)
    {
        cpu->cur_ip = *arg_ptr - 1;
    }
})

DEF_CMD(JNE, JUMP, 1, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);

    if(l_val != h_val)
    {
        cpu->cur_ip = *arg_ptr - 1;
    }  
})

DEF_CMD(JG, JUMP, 1, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);

    if(l_val > h_val)
    {
        cpu->cur_ip = *arg_ptr - 1;
    }  
})

DEF_CMD(JL, JUMP, 1, 
{
    stack_pop(cpu->stack, &h_val);
    stack_pop(cpu->stack, &l_val);

    if(l_val < h_val)
    {
        cpu->cur_ip = *arg_ptr - 1;
    }  
})

DEF_CMD(CALL, JUMP, 1, 
{
    stack_push(cpu->stack, (int)(cpu->cur_ip + 1));

    cpu->cur_ip = *arg_ptr - 1;
})
