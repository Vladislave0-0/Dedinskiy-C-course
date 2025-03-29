#include "./RecursiveDescent.h"

//==================================================================================================================================

int file_processing(struct Tree* tree, const char* filename)
{
    tree->mainfile = fopen(filename, "rb");

    if(tree->mainfile == nullptr)
    {
        tree->error_code = ERROR_OPEN_MAINFILE;

        RETURN_DIFF_ERROR(ERROR_OPEN_MAINFILE);
    }

    num_of_chars(tree, filename);

    chars_buffer(tree, tree->mainfile);

    fclose(tree->mainfile);

    return SUCCESS;
}

//==================================================================================================================================

int num_of_chars(struct Tree* tree, const char* filename)
{
    struct stat buf = {};

    stat(filename, &buf);

    if(buf.st_size <= 0)
    {
        tree->error_code = ERROR_NUM_OF_CHARS;

        RETURN_DIFF_ERROR(ERROR_NUM_OF_CHARS);
    }

    tree->chars_num =  buf.st_size;

    return SUCCESS;
}

//==================================================================================================================================

int chars_buffer(struct Tree* tree, FILE* stream)
{
    tree->buffer_ptr = (char*)calloc(tree->chars_num + 1, sizeof(char));
    if(tree->buffer_ptr == nullptr)
    {
        tree->error_code = ERROR_BUFFER_CALLOC;

        RETURN_DIFF_ERROR(ERROR_BUFFER_CALLOC);
    }


    size_t fread_ch = fread(tree->buffer_ptr, sizeof(char), tree->chars_num, stream);
    if(fread_ch != tree->chars_num)
    {
        tree->error_code = ERROR_FREAD;

        RETURN_DIFF_ERROR(ERROR_FREAD);
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
    if(new_buffer == nullptr)
    {
        tree->error_code = ERROR_NEW_BUFFER_CALLOC;

        RETURN_DIFF_ERROR(ERROR_NEW_BUFFER_CALLOC);
    }


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

    return SUCCESS;
}

//==================================================================================================================================

int variables_processing(struct Tree* tree)
{
    printf(CYN "Hello! Enter the number of variables: " WHT);
    scanf("%d", &(tree->vars_num));


    tree->vars_arr = (Var*)calloc(tree->vars_num, sizeof(Var));
    if(tree->vars_arr == nullptr)
    {
        tree->error_code = ERROR_VARIABLES_CALLOC;

        RETURN_DIFF_ERROR(ERROR_VARIABLES_CALLOC);
    }


    for(int i = 0; i < tree->vars_num; i++)
    {
        printf(CYN "\nEnter the #%d variable: " WHT, i + 1);
        scanf("%s", (tree->vars_arr[i].text));

        printf(CYN "Enter the value of variable %s: " WHT, tree->vars_arr[i].text);
        scanf("%lf" RESET, &(tree->vars_arr[i].value));
    }

    return SUCCESS;
}

//==================================================================================================================================

Node* make_tree(struct Tree* tree)
{
    Node* root = getGen(tree);

    if(root == nullptr)
    {
        tree->error_code = ERROR_FILE_SYNTAX;

        printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);
    }

    return root;
}

//==================================================================================================================================

Node* getGen(struct Tree* tree)
{    
    Node* root = getExp(tree);

    if(STR[STR_POS] != '\0')
    {
        return nullptr;
    }

    return root;
}

//==================================================================================================================================

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

        if(right_child == nullptr)
        {
            return nullptr;
        }

        parent->right_child = right_child;

        left_child = parent;
    }

    return left_child;
}

//==================================================================================================================================

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
        if(right_child == nullptr)
        {
            return nullptr;
        }

        parent->right_child = right_child;

        left_child = parent;
    }

    return left_child;
}

//==================================================================================================================================

Node* getDeg(struct Tree* tree)
{
    Node* left_child  = getBrt(tree);
    Node* right_child = nullptr;
    Node* parent      = nullptr;

    while(STR[STR_POS] == '^')
    {
        STR_POS++;

        right_child = getBrt(tree);

        if(right_child == nullptr)
        {
            return nullptr;
        }

        parent = POW_NODE(left_child, right_child);

        left_child = parent;
    }

    return left_child;
}

//==================================================================================================================================

Node* getBrt(struct Tree* tree)
{
    Node* node = nullptr;

    if(STR[STR_POS] == '(')
    {
        STR_POS++;

        node = getExp(tree);

        if(STR[STR_POS++] != ')')
        {
            return nullptr;
        }
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

//==================================================================================================================================

Node* getWord(struct Tree* tree)
{
    Node* node = nullptr;

    char* variable = getVar(tree);

    if(variable == nullptr)
    {
        tree->error_code = ERROR_GET_VAR_CALLOC;

        printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);

        return nullptr;
    }

    if(STR[STR_POS] == '(')
    {
        STR_POS++;

        Node* arg_node = getExp(tree);

        if(     !strcasecmp(variable, "sqrt"))      node = SQRT_NODE  (arg_node);
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
        else return nullptr;

        if(STR[STR_POS++] != ')')
        {
            return nullptr;
        }

        free(variable);
        variable = nullptr;
    }

    else
    {
        if(find_var(tree, variable) == 0)
        {
            if(add_var(tree, variable) == nullptr)
            {
                tree->error_code = ERROR_ADD_VAR_REALLOC;

                printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                            "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);

                return nullptr;
            }
        }

        if(tree->vars_num_to_free >= INIT_WORDS_NUM - 1)
        {
            printf(RED "Ohh, INIT_WORDS_NUM in Tree.h is small. Increase it!" RESET);
        }

        tree->vars_to_free[tree->vars_num_to_free++] = variable;

        node = CREATE_VAR(variable);
    }

    return node;
}

//==================================================================================================================================

char* getVar(struct Tree* tree)
{
    char* variable = (char*)calloc(MAX_WORD_LEN, sizeof(char));

    if(variable == nullptr)
    {
        return nullptr;
    }

    for(int i = 0; (STR[STR_POS] >= 'A' && STR[STR_POS] <= 'Z') || (STR[STR_POS] >= 'a' && STR[STR_POS] <= 'z'); i++, STR_POS++)
    {
        variable[i] = STR[STR_POS];
    }

    return variable;
}

//==================================================================================================================================

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

//==================================================================================================================================

Var* add_var(struct Tree* tree, char* variable)
{
    tree->vars_arr = (Var*)realloc(tree->vars_arr, (tree->vars_num + 1) * sizeof(Var));

    if(tree->vars_arr == nullptr)
    {
        return nullptr;
    }

    strcpy(tree->vars_arr[tree->vars_num].text, variable);

    tree->vars_arr[tree->vars_num++].value = POISON;

    return tree->vars_arr;
}

//==================================================================================================================================

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

    if(STR_POS <= calls_num)
    {
        tree->error_code = ERROR_GET_NUM;

        printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                    "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);

        return nullptr;
    }

    return CREATE_NUM(val);
}
