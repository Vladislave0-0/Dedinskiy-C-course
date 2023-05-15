#include "RecursiveDescent.h"
#include <math.h>
#include "DSL.h"

//======================================================================

void file_processing(struct Tree* tree, const char* filename)
{
    tree->mainfile = fopen(filename, "rb");

    if(tree->mainfile == nullptr)
    {
        printf("BAD_MAINFILE\n");

        return;
    }

    num_of_chars(tree, filename);

    chars_buffer(tree, tree->mainfile);

    fclose(tree->mainfile);
}

//======================================================================

void num_of_chars(struct Tree* tree, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    if(buf.st_size <= 0)
    {
        printf("BAD_CHARS_NUM\n");

        return;
    }

    tree->chars_num =  buf.st_size;
}

//======================================================================

void chars_buffer(struct Tree* tree, FILE* stream)
{
    tree->buffer_ptr = (char*)calloc(tree->chars_num + 1, sizeof(char));

    if(tree->buffer_ptr == nullptr)
    {
        printf("BAD_CHARS_BUFFER\n");

        return;
    }

    size_t fread_ch = fread(tree->buffer_ptr, sizeof(char), tree->chars_num, stream);

    if(fread_ch != tree->chars_num)
    {
        printf("BAD_FREAD\n");

        return;
    }

    tree->buffer_ptr[tree->chars_num] = '\0';

    int sep_num = 0;

    for(size_t i = 0; i < tree->chars_num; i++)
    {
        if((tree->buffer_ptr[i] == ' ') || (tree->buffer_ptr[i] == '\n'))
        {
            sep_num++;
        }
    }

    char* new_buffer = (char*)calloc(tree->chars_num - sep_num + 1, sizeof(char));

    size_t new_buf = 0;
    size_t old_buf = 0;

    for(; old_buf < tree->chars_num; new_buf++, old_buf++)
    {
        while((tree->buffer_ptr[old_buf] == ' ') || (tree->buffer_ptr[old_buf] == '\n'))
        {
            old_buf++;
        }

        new_buffer[new_buf] = tree->buffer_ptr[old_buf];
    }

    new_buffer[tree->chars_num - sep_num] = '\0';

    free(tree->buffer_ptr);

    tree->buffer_ptr = new_buffer;
}

//======================================================================

void variables_processing(struct Tree* tree)
{
    printf(CYN "Hello! Enter the number of variables: " WHT);

    scanf("%d", &(tree->vars_num));

    tree->vars_arr = (Var*)calloc(tree->vars_num, sizeof(Var));

    assert(tree->vars_arr != nullptr);

    for(int i = 0; i < tree->vars_num; i++)
    {
        printf(CYN "\nEnter the #%d variable: " WHT, i + 1);
        scanf("%s", (tree->vars_arr[i].text));

        printf(CYN "Enter the value of variable %s: " WHT, tree->vars_arr[i].text);
        scanf("%lf" RESET, &(tree->vars_arr[i].value));
    }

    // for(int i = 0; i < tree->vars_num; i++)
    // {
    //     printf("\n\nVar_%d: %s --- %lf\n", i + 1, tree->vars_arr[i].text, tree->vars_arr[i].value);
    // }
}

//======================================================================

Node* make_tree(struct Tree* tree)
{
    Node* root = getGen(tree);

    return root;
}

//======================================================================

Node* getGen(struct Tree* tree)
{    
    Node* root = getExp(tree);

    assert(STR[STR_POS] == '\0');

    return root;
}

//==============================================================================

Node* getExp(struct Tree* tree)
{
    Node* left_child  = getMul(tree);
    Node* right_child = nullptr;
    Node* parent      = nullptr;

    while(STR[STR_POS] == '+' || STR[STR_POS] == '-')
    {
        if(STR[STR_POS] == '+')
        {
            STR_POS++;

            parent = ADD_NODE(left_child, nullptr);
        }

        else
        {
            STR_POS++;

            parent = SUB_NODE(left_child, nullptr);
        }

        right_child = getMul(tree);

        parent->right_child = right_child;

        left_child = parent;
    }

    return left_child;
}

//==============================================================================

Node* getMul(struct Tree* tree)
{
    Node* left_child  = getDeg(tree);
    Node* right_child = nullptr;
    Node* parent      = nullptr; 

    while(STR[STR_POS] == '*' || STR[STR_POS] == '/')
    {
        if(STR[STR_POS] == '*')
        {
            STR_POS++;

            parent = MUL_NODE(left_child, nullptr);
        }

        else
        {
            STR_POS++;

            parent = DIV_NODE(left_child, nullptr);
        }

        right_child = getDeg(tree);

        parent->right_child = right_child;

        left_child = parent;
    }

    return left_child;
}

//==============================================================================

Node* getDeg(struct Tree* tree)
{
    Node* left_child  = getBrt(tree);
    Node* right_child = nullptr;
    Node* parent      = nullptr;

    if(STR[STR_POS] == '^')
    {
        STR_POS++;

        right_child = getBrt(tree);

        parent = POW_NODE(left_child, right_child);

        left_child = parent;
    }

    return left_child;
}

//==============================================================================

Node* getBrt(struct Tree* tree)
{
    Node* node = nullptr;

    if(STR[STR_POS] == '(')
    {
        STR_POS++;

        node = getExp(tree);

        assert(STR[STR_POS++] == ')');
    }

    else if((STR[STR_POS] >= '0' && STR[STR_POS] <= '9') || (STR[STR_POS] == '-'))
    {
        node = getNum(tree);
    }

    else
    {
        node = getWord(tree);
    }

    return node;
}

//==============================================================================

Node* getWord(struct Tree* tree)
{
    Node* node = nullptr;

    char* variable = getVar(tree);

    if(STR[STR_POS] == '(')
    {
        STR_POS++;

        Node* arg_node = getExp(tree);

        if(!strcasecmp(variable, "sqrt"))           node = SQRT_NODE  (arg_node);
        else if(!strcasecmp(variable, "sin"))       node = SIN_NODE   (arg_node);
        else if(!strcasecmp(variable, "cos"))       node = COS_NODE   (arg_node);
        else if(!strcasecmp(variable, "tg"))        node = TG_NODE    (arg_node);
        else if(!strcasecmp(variable, "ctg"))       node = CTG_NODE   (arg_node);
        else if(!strcasecmp(variable, "arcsin"))    node = ARCSIN_NODE(arg_node);
        else if(!strcasecmp(variable, "arccos"))    node = ARCCOS_NODE(arg_node);
        else if(!strcasecmp(variable, "arctg"))     node = ARCTG_NODE (arg_node);
        else if(!strcasecmp(variable, "arcctg"))    node = ARCCTG_NODE(arg_node);
        else if(!strcasecmp(variable, "sh"))        node = SH_NODE    (arg_node);
        else if(!strcasecmp(variable, "ch"))        node = CH_NODE    (arg_node);
        else if(!strcasecmp(variable, "ln"))        node = LN_NODE    (arg_node);
        else if(!strcasecmp(variable, "exp"))       node = EXP_NODE   (arg_node);

        assert(STR[STR_POS++] == ')');
        free(variable);
    }

    else
    {
        if(find_var(tree, variable) == 0)
        {
            add_var(tree, variable);
        }

        tree->vars_to_free[tree->vars_num_to_free++] = variable;

        node = CREATE_VAR(variable);
    }


    return node;
}

//==============================================================================

char* getVar(struct Tree* tree)
{
    char* variable = (char*)calloc(MAX_WORD_LEN, sizeof(char));

    assert(variable != nullptr);

    for(int i = 0; (STR[STR_POS] >= 'A' && STR[STR_POS] <= 'Z') || (STR[STR_POS] >= 'a' && STR[STR_POS] <= 'z'); i++, STR_POS++)
    {
        variable[i] = STR[STR_POS];
    }

    return variable;
}

//==============================================================================

int find_var(struct Tree* tree, char* variable)
{
    for(int i = 0; i < tree->vars_num; i++)
    {
        if(strcasecmp(tree->vars_arr[i].text, variable) == 0)
        {
            return 1;
        }
    }

    return 0;
}

//==============================================================================

void add_var(struct Tree* tree, char* variable)
{
    tree->vars_arr = (Var*)realloc(tree->vars_arr, (tree->vars_num + 1)* sizeof(Var));

    assert(tree->vars_arr != nullptr);

    strcpy(tree->vars_arr[tree->vars_num].text, variable);

    tree->vars_arr[tree->vars_num].value = POISON;

    tree->vars_num++;
}

//==============================================================================

Node* getNum(struct Tree* tree)
{
    double val = 0;
    int calls_num = STR_POS;
    char num_in_str[30];

    if(('0' <= STR[STR_POS] && STR[STR_POS] <= '9') || (STR[STR_POS] == '-'))
    {
        val = atof(STR + STR_POS);
        
        sprintf(num_in_str, "%f", val);

        STR[STR_POS] == '-' ? (STR_POS++) : STR_POS;

        for(; ('0' <= STR[STR_POS] && STR[STR_POS] <= '9') || (STR[STR_POS] == '.'); STR_POS++)
            ;
    }

    assert(STR_POS > calls_num);

    return CREATE_NUM(val);
}
