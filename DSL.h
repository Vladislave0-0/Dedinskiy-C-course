#define STR_POS tree->str_pos
#define STR     tree->buffer_ptr

#define CREATE_OP(left_child, right_child, op_val)   create_node(left_child, right_child, OP, nullptr, 0, op_val)
#define CREATE_FUNC(right_child, func_name)          create_node(nullptr, right_child, FUNC, func_name, 0, ' ')
#define CREATE_VAR(var_name)                         create_node(nullptr, nullptr, VAR, var_name, 0, ' ') 
#define CREATE_NUM(num)                              create_node(nullptr, nullptr, NUM, nullptr, num, ' ')
#define CREATE_NODE                                  create_node(nullptr, nullptr, NUL, nullptr, 0, 0)

#define ADD_NODE(left_child, right_child) CREATE_OP(left_child, right_child, '+')
#define SUB_NODE(left_child, right_child) CREATE_OP(left_child, right_child, '-')
#define MUL_NODE(left_child, right_child) CREATE_OP(left_child, right_child, '*')
#define DIV_NODE(left_child, right_child) CREATE_OP(left_child, right_child, '/')
#define POW_NODE(left_child, right_child) CREATE_OP(left_child, right_child, '^')

#define SQRT_NODE(  right_child) CREATE_FUNC(right_child, "sqrt")
#define SIN_NODE(   right_child) CREATE_FUNC(right_child, "sin")
#define COS_NODE(   right_child) CREATE_FUNC(right_child, "cos")
#define TG_NODE(    right_child) CREATE_FUNC(right_child, "tg")
#define CTG_NODE(   right_child) CREATE_FUNC(right_child, "ctg")
#define ARCSIN_NODE(right_child) CREATE_FUNC(right_child, "arcsin")
#define ARCCOS_NODE(right_child) CREATE_FUNC(right_child, "arccos")
#define ARCTG_NODE( right_child) CREATE_FUNC(right_child, "arctg")
#define ARCCTG_NODE(right_child) CREATE_FUNC(right_child, "arcctg")
#define SH_NODE(    right_child) CREATE_FUNC(right_child, "sh")
#define CH_NODE(    right_child) CREATE_FUNC(right_child, "ch")
#define LN_NODE(    right_child) CREATE_FUNC(right_child, "ln")
#define EXP_NODE(   right_child) CREATE_FUNC(right_child, "exp")