#ifndef TREE_H
#define TREE_H

//======================================================================

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//======================================================================

const int MAX_WORD_LEN = 30;
const int POISON       = 0xDEAD;

//======================================================================

union Value
{
    char op_code;
    double number;
    const char* var;
};

enum NodeType
{
    NUL = 0,
    NUM = 1,
    OP  = 2,
    VAR = 3,
    FUNC = 4,
};

struct Node
{
    NodeType type;
    Value val;

    Node* parent    = nullptr;
    Node* left_child  = nullptr;
    Node* right_child = nullptr;    
};

struct Var
{
    char text[MAX_WORD_LEN] = {};
    double value = POISON;
};

struct Tree
{
    FILE* mainfile    = nullptr;
    Node* root        = nullptr;
    char* buffer_ptr  = nullptr;
    Var* vars_arr     = nullptr;

    size_t chars_num  = 0;
    int vars_num      = 0;
    int str_pos       = 0;

    char* vars_to_free[15];
    int vars_num_to_free = 0;

    int error_code = 0;
};

//==================================================================================================================

Tree* tree_ctor();

//==================================================================================================================

Node* create_node(Node* left_child, Node* right_child, NodeType type, const char* var, double value, char op_code);

//==================================================================================================================

// void print_tree(Node* node, PrintoutMode mode);

//==================================================================================================================

// void print_preorder(Node* node);

//==================================================================================================================

// void print_postorder(Node* node);

//==================================================================================================================

// void print_inorder(Node* node);

//==================================================================================================================

void tree_dtor(struct Tree* tree);

//==================================================================================================================

void childs_dtor(struct Node* node);

//==================================================================================================================

void variable_substitution(Tree* init_tree, Node* root);

//==================================================================================================================

#endif // TREE_H
