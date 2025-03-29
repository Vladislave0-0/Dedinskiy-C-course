#ifndef RECURSIVE_DESCENT_H
#define RECURSIVE_DESCENT_H

//======================================================================

#include <sys/stat.h>

#include "./Tree.h"

//======================================================================
/**
 * @brief File processing input.txt.
 * 
 * @param tree initial tree
 * @param filename file name
 * @return int 
 */
int file_processing(struct Tree* tree, const char* filename);

//======================================================================
/**
 * @brief Counting the number of characters.
 * 
 * @param tree initial tree
 * @param filename file name
 * @return int 
 */
int num_of_chars(struct Tree* tree, const char* filename);

//======================================================================
/**
 * @brief Reserving memory for a buffer and copying text from a 
 *        file to it input.txt
 * 
 * @param tree initial tree
 * @param stream file pointer
 * @return int 
 */
int chars_buffer(struct Tree* tree, FILE* stream);

//======================================================================
/**
 * @brief Processing of user-entered variables.
 * 
 * @param tree initial tree
 * @return int 
 */
int variables_processing(struct Tree* tree);

//======================================================================
/**
 * @brief A function to start recursive reading of a file using the 
 *        Extended Backus–Naur Form (EBNF) formal grammar). Description:
 *        
 *        getGen  ::= getExp'\0'
 *        getExp  ::= getMul{['+' | '-']getMul}*
 *        getMul  ::= getDeg{['*' | '/']getDeg}*
 *        getDeg  ::= getBrt {&& if '^' then getBrt}*
 *        getBrt  ::= '(' getExp ')' | getNum | getWord
 *        getWord ::= getVar && if '(' then getExp ')'
 *        getVar  ::= ['A' - 'z']+
 *        getNum  ::= ['0' - '9']+
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* make_tree(struct Tree* tree);

//======================================================================
/**
 * @brief To start a recursive descent and find the ending symbol.
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getGen(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding expressions.
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getExp(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding multiplications.
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getMul(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding degrees.
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getDeg(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding brackets. 
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getBrt(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding words (variables or functions).
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getWord(struct Tree* tree);

//==============================================================================
/**
 * @brief EBNF rule for finding variables.
 * 
 * @param tree initial tree
 * @return Node* 
 */
char* getVar(struct Tree* tree);

//==============================================================================
/**
 * @brief Auxiliary function for checking the presence of this variable in an 
 *        array of variables
 * 
 * @param tree initial tree
 * @param variable variable
 * @return int 
 */
int find_var(struct Tree* tree, char* variable);

//==============================================================================
/**
 * @brief Auxiliary function for adding a function to a special array for 
 *        further memory release.
 * 
 * @param tree initial tree
 * @param variable variable
 * @return Var* 
 */
Var* add_var(struct Tree* tree, char* variable);

//==============================================================================
/**
 * @brief EBNF rule for finding numbers.
 * 
 * @param tree initial tree
 * @return Node* 
 */
Node* getNum(struct Tree* tree);

//==============================================================================

#endif // RECURSIVE_DESCENT_H
