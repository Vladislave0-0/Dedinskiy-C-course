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
const int INIT_WORDS_NUM   = 100;

//==================================================================================================================

enum NodeType
{
    NUL  = 0,       //| Unknown node type.
    NUM  = 1,       //| Node with number.
    OP   = 2,       //| Node with operator.
    VAR  = 3,       //| Node with variable.
    FUNC = 4,       //| Node with function.
};

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

// enum for function float_comparison
enum ComparisonResult
{
    UNDER = -1,
    EQUAL =  0,
    OVER  =  1,
};

//==================================================================================================================

union Value
{
    char op_code;
    double number;
    const char* var;
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
    FILE* mainfile    = nullptr;            //| The file from which the initial tree is built.
    Node* root        = nullptr;            //| The root from which the tree begins after reading.
    char* buffer_ptr  = nullptr;            //| The buffer in which the text from the file is stored.
    Var* vars_arr     = nullptr;            //| Array of all variables in the tree.

    size_t chars_num  = 0;                  //| The number of characters in the source file.
    int vars_num      = 0;                  //| The number of variables in the tree.
    int str_pos       = 0;                  //| Current buffer read position.

    char* vars_to_free[INIT_WORDS_NUM];     //| Variables that should be deleted at the end, and the memory for them is freed.
    int vars_num_to_free = 0;               //| The number of variables that should be deleted at the end, and the memory for them is freed.

    int error_code = 0;                     //| Error code.
};

//==================================================================================================================
/**
 * @brief Function for creating a tree.
 * 
 * @return Tree* 
 */
Tree* tree_ctor();

//==================================================================================================================
/**
 * @brief Function for creating the initial tree.
 * 
 * @param tree_filename name of input file
 * @return Tree* 
 */
Tree* init_tree_ctor(const char* tree_filename);

//==================================================================================================================
/**
 * @brief Function for opening a file.
 * 
 * @param tree initial tree
 * @param filename name of input file
 * @return FILE* 
 */
FILE* file_open(Tree* tree, const char* filename);

//==================================================================================================================
/**
 * @brief Function for creating and filling a node.
 * 
 * @param left_child the node connected on the left to the created node on the left
 * @param right_child the node connected on the left to the created node on the right
 * @param type type of the node
 * @param var text of the variable node or function node
 * @param value value of number node
 * @param op_code ASCII code of operational code
 * @return Node* 
 */
Node* create_node(Node* left_child, Node* right_child, NodeType type, const char* var, double value, char op_code);

//==================================================================================================================
/**
 * @brief Destructor of the initial tree.
 * 
 * @param tree initial tree
 */
void init_tree_dtor(struct Tree* tree);

//==================================================================================================================
/**
 * @brief Destructor of some tree.
 * 
 * @param some_tree 
 */
void other_tree_dtor(Tree* some_tree);

//==================================================================================================================
/**
 * @brief Subtree destructor.
 * 
 * @param node the node from which the destructor will start working.
 */
void childs_dtor(struct Node* node);

//==================================================================================================================
/**
 * @brief Substitution of their values entered by the user instead of variables.
 * 
 * @param init_tree initial tree
 * @param root the node from which the substitution will begin
 */
void variable_substitution(Tree* init_tree, Node* root);

//==================================================================================================================
/**
 * @brief Copying a subtree.
 * 
 * @param some_node the node to which we copy
 * @param root the node from which we copy
 */
void node_copy(struct Node* some_node, struct Node* root);

//==================================================================================================================
/**
 * @brief Filling the field "parent" in the subtree.
 * 
 * @param root the node from which the filling begins
 */
void parents_copy(struct Node* root);

//==================================================================================================================
/**
 * @brief Calculating a tree as an expression.
 * 
 * @param root root of the tree
 */
void func_like_eval(struct Node* root);

//==================================================================================================================
/**
 * @brief A function for comparing float numbers with an accuracy of 6 digits after the decimal point.
 * 
 * @param x1 first number
 * @param x2 second number
 * @return ComparisonResult 
 */
ComparisonResult float_comparison(const double x1, const double x2);

//==================================================================================================================

#endif // TREE_H
