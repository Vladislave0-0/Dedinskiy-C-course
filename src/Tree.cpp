#include <math.h>

#include "./RecursiveDescent.h"

//================================================================================================================

Tree* tree_ctor()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

    if(tree == nullptr)
    {   
        tree->error_code = ERROR_TREE_INIZIALIZATION;

        printf(RED "In function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);
    }

    return tree;
}

//================================================================================================================

Tree* init_tree_ctor(const char* tree_filename)
{
    Tree* tree = tree_ctor();

    if(tree->error_code != 0)
    {
        return nullptr;
    }

    file_processing(tree, tree_filename);

    variables_processing(tree);

    return tree;
}

//================================================================================================================

FILE* file_open(Tree* tree, const char* filename)
{
    FILE* file = fopen(filename, "w");

    if(file == nullptr)
    {
        tree->error_code = ERROR_OPEN_TEX_FILE;

        printf(RED "In function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, tree->error_code);
    }

    return file;
}

//================================================================================================================

Node* create_node(Node* left_child, Node* right_child, NodeType type, const char* var, double value, char op_code)
{
    Node* node = (Node*)calloc(1, sizeof(Node));

    if(node == nullptr)
    {
        printf(RED "In function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, ERROR_CREATE_NODE);

        return nullptr;
    }

    node->type = type;

    if(type == NUM)
    {
        node->val.number = value;
    }

    else if(type == OP)
    {
        node->val.op_code = op_code;
    }

    else if(((type == VAR) || (type == FUNC)) && (var != nullptr))
    {
        node->val.var = var;
    }

    node->left_child = left_child;
    node->right_child = right_child;

    return node;
}

//================================================================================================================

void init_tree_dtor(struct Tree* tree)
{
    childs_dtor(tree->root);

    free(tree->buffer_ptr);
    tree->buffer_ptr = nullptr;

    for(int i = 0; i < tree->vars_num_to_free; i++)
    {
        free(tree->vars_to_free[i]);
        tree->vars_to_free[i] = nullptr;
    }

    free(tree->vars_arr);
    tree->vars_arr = nullptr;

    free(tree);
    tree = nullptr;

    printf(GRN "\nThe program was executed successfully!\n" RESET);
}

//================================================================================================================

void childs_dtor(struct Node* node)
{
    if(node == nullptr)
    {
        return;
    }

    if(node->left_child != nullptr)
    {
        childs_dtor(node->left_child);
    }

    if(node->right_child != nullptr)
    {
        childs_dtor(node->right_child);
    }

    if(node != nullptr)
    {
        node->val.number = POISON;
        node->type = NUL;
        free(node);
        node = nullptr;
    }
}

//================================================================================================================

void variable_substitution(Tree* init_tree, Node* root)
{
    if(root->left_child != nullptr)
    {
        variable_substitution(init_tree, root->left_child);
    }

    if(root->right_child != nullptr)
    {
        variable_substitution(init_tree, root->right_child);
    }

    if(root->type == VAR)
    {
        for(int i = 0; i < init_tree->vars_num; i++)
        {
            if(strcmp(root->val.var, init_tree->vars_arr[i].text) == 0)
            {
                root->type = NUM;

                root->val.number = init_tree->vars_arr[i].value;
                return;
            }
        }
    }
}

//================================================================================================================

void node_copy(struct Node* diff_node, struct Node* root)
{
    diff_node->type   = root->type;
    diff_node->parent = root->parent;

    if(diff_node->type == NUM)
    {
        diff_node->val.number = root->val.number;
    }

    else if(diff_node->type == OP)
    {
        diff_node->val.op_code = root->val.op_code;
    }

    else if((diff_node->type == VAR) || (diff_node->type == FUNC))
    {
        diff_node->val.var = root->val.var;
    }

    if(root->left_child != nullptr)
    {
        diff_node->left_child = CREATE_NODE;
        node_copy(diff_node->left_child, root->left_child);
    }

    else
    {
        diff_node->left_child = nullptr;
    }

    if(root->right_child != nullptr)
    {
        diff_node->right_child = CREATE_NODE;
        node_copy(diff_node->right_child, root->right_child);
    }

    else
    {
        diff_node->right_child = nullptr;
    }
}

//================================================================================================================

void parents_copy(struct Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    if(root->left_child != nullptr)
    {
        root->left_child->parent = root;
        parents_copy(root->left_child);
    }

    if(root->right_child != nullptr)
    {
        root->right_child->parent = root;
        parents_copy(root->right_child);
    }
}

//================================================================================================================

void func_like_eval(struct Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    if(root->type == OP)
    {
        if(root->left_child->type != NUM)
        {
            func_like_eval(root->left_child);
        }

        if(root->right_child->type != NUM)
        {
            func_like_eval(root->right_child);
        }

        double val = 0;

        switch(root->val.op_code)
        {
            case('+'): val = root->left_child->val.number + root->right_child->val.number;     break;
            case('-'): val = root->left_child->val.number - root->right_child->val.number;     break;     
            case('*'): val = root->left_child->val.number * root->right_child->val.number;     break;
            case('/'): val = root->left_child->val.number / root->right_child->val.number;     break;            
            case('^'): val = pow(root->left_child->val.number, root->right_child->val.number); break;

            default: printf(RED "\nUNKNOWN OPERATOR IN FUNC_LIKE_EVAL\n\n" RESET);
        }


        root->type = NUM;
        root->val.number = val;
        childs_dtor(root->left_child);
        root->left_child = nullptr;
        childs_dtor(root->right_child);
        root->right_child = nullptr;
    }

    if(root->type == FUNC)
    {
        if(root->right_child->type != NUM)
        {
            func_like_eval(root->right_child);
        }

        double val = 0;

        if(     !strcasecmp(root->val.var, "sqrt"))      val = sqrt(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "sin"))       val = sin(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "cos"))       val = cos(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "tg"))        val = tan(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "ctg"))       val = 1/tan(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "arcsin"))    val = asin(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "arccos"))    val = acos(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "arctg"))     val = atan(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "arcctg"))    val = M_PI/2 - atan(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "sh"))        val = sinh(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "ch"))        val = cosh(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "ln"))        val = log(root->right_child->val.number);
        else if(!strcasecmp(root->val.var, "exp"))       val = exp(root->right_child->val.number);

        root->type = NUM;
        root->val.number = val;
        childs_dtor(root->right_child);
        root->right_child = nullptr;
    }
}

//================================================================================================================

ComparisonResult float_comparison(const double x1, const double x2)
{
    if (fabs(x1 - x2) <= FloatConstant)
    {
        return EQUAL;
    }

    else 
    {
        return ((x1-x2) > FloatConstant) ? OVER : UNDER;
    }
}
