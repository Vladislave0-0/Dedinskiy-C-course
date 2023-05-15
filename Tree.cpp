#include "Tree.h"

//====================================================================================================================

Tree* tree_ctor()
{
    Tree* tree = (Tree*)calloc(1, sizeof(Tree));

    if(tree == nullptr)
    {   
        printf("BAD_TREE_CALLOC\n");
    }

    return tree;
}

//====================================================================================================================

Node* create_node(Node* left_child, Node* right_child, NodeType type, const char* var, double value, char op_code)
{
    Node* node = (Node*)calloc(1, sizeof(Node));

    if(node == nullptr)
    {
        printf("ПИЗДА РУЛЮ\n");
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

//====================================================================================================================

// void print_tree(Node* node, PrintoutMode mode)
// {
//     switch(mode)
//     {
//         case(IN_ORDER):
//         {
//             print_inorder(node);

//             break;
//         }

//         case(PRE_ORDER):
//         {
//             print_preorder(node);

//             break;
//         }

//         case(POST_ORDER):
//         {
//             print_postorder(node);
    
//             break;
//         }

//         default:
//             printf("ПИЗДА РУЛЮ\n");
//     }

//     printf("\n");
// }

//====================================================================================================================

// void print_preorder(Node* node)
// {
//     if(node == nullptr)
//     {
//         return;
//     }
    
//     if(node->type == NUM)
//     {
//         printf("%lf  ", node->val.number);
//     }

//     else if(node->type == OP)
//     {
//         printf("%c  ", node->val.op_code);
//     }

//     else if(node->type == VAR)
//     {
//         printf("%s  ", node->val.var);
//     }

//     print_preorder(node->left_child);

//     print_preorder(node->right_child);
// }

// //====================================================================================================================

// void print_inorder(Node* node)
// {
//     if(node == nullptr)
//     {
//         return;
//     }

//     print_inorder(node->left_child);

//     if(node->type == NUM)
//     {
//         printf("%lf  ", node->val.number);
//     }

//     else if(node->type == OP)
//     {
//         printf("%c  ", node->val.op_code);
//     }

//     else if(node->type == VAR)
//     {
//         printf("%s  ", node->val.var);
//     }

//     print_inorder(node->right_child);
// }

// //====================================================================================================================

// void print_postorder(Node* node)
// {
//     if(node == nullptr)
//     {
//         return;
//     }

//     print_postorder(node->left_child);

//     print_postorder(node->right_child);

//     if(node->type == NUM)
//     {
//         printf("%lf  ", node->val.number);
//     }

//     else if(node->type == OP)
//     {
//         printf("%c  ", node->val.op_code);
//     }

//     else if(node->type == VAR)
//     {
//         printf("%s  ", node->val.var);
//     }
// }

//======================================================================

void tree_dtor(struct Tree* tree)
{
    childs_dtor(tree->root);

    free(tree->buffer_ptr);

    for(int i = 0; i < tree->vars_num_to_free; i++)
    {
        free(tree->vars_to_free[i]);
    }

    free(tree->vars_arr);

    free(tree);
}

//======================================================================

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

//======================================================================

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
