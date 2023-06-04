#ifndef TREE_H
#define TREE_H

//==================================================================================================================

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../Include/DSL.h"
#include "../Include/Colors.h"

//==================================================================================================================

#define RETURN_DIFF_ERROR(error_code)                                                                       \
        printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "        \
                   "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, error_code);       \
        return error_code;                                                                                  \

//==================================================================================================================

const int MAX_WORD_LEN     = 30;
const int POISON           = 0xDEAD;
const double FloatConstant = 1E-6;

//==================================================================================================================

enum ComparisonResult
{
    UNDER = -1,
    EQUAL =  0,
    OVER  =  1,
};


union Value
{
    char op_code;
    double number;
    const char* var;
};


enum NodeType
{
    NUL  = 0,
    NUM  = 1,
    OP   = 2,
    VAR  = 3,
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

    char* vars_to_free[400];
    int vars_num_to_free = 0;

    int error_code = 0;
};

//===============================================================================================================

enum ProgrammErrors
{
    SUCCESS                   = 0,
    ERROR_TREE_INIZIALIZATION = 1,
    ERROR_OPEN_MAINFILE       = 2,
    ERROR_OPEN_TEX_FILE       = 3,
    ERROR_NUM_OF_CHARS        = 4,
    ERROR_BUFFER_CALLOC       = 5,
    ERROR_FREAD               = 6,
    ERROR_NEW_BUFFER_CALLOC   = 7,
    ERROR_VARIABLES_CALLOC    = 8,
    ERROR_FILE_SYNTAX         = 9,
    ERROR_GET_VAR_CALLOC      = 10,
    ERROR_ADD_VAR_REALLOC     = 11,
    ERROR_GET_NUM             = 12,
    ERROR_BAD_SIMPLIFICATION  = 13,
    ERROR_DEVISION_BY_ZERO    = 14,
    ERROR_NEG_NUMBER_DEGREE   = 15,
    ERROR_OPEN_GRAPHVIZ_FILE  = 16,
    ERROR_CREATE_NODE         = 17,
};

//==================================================================================================================

Tree* tree_ctor();


Tree* init_tree_ctor(const char* tree_filename);

//==================================================================================================================

FILE* file_open(Tree* tree, const char* filename);

//==================================================================================================================

Node* create_node(Node* left_child, Node* right_child, NodeType type, const char* var, double value, char op_code);

//==================================================================================================================

void init_tree_dtor(struct Tree* tree);

//==================================================================================================================

void childs_dtor(struct Node* node);

//==================================================================================================================

void variable_substitution(Tree* init_tree, Node* root);

//==================================================================================================================

void node_copy(struct Node* diff_node, struct Node* root);

//==================================================================================================================

void parents_copy(struct Node* root);

//==================================================================================================================

void func_like_eval(struct Node* root);

//==================================================================================================================

ComparisonResult float_comparison(const double x1, const double x2);

//==================================================================================================================

#endif // TREE_H
