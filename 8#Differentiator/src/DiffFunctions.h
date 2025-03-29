#ifndef DIFF_FUNCTIONS_H
#define DIFF_FUNCTIONS_H

//========================================================================================

#include "./Tree.h"

//========================================================================================
/**
 * @brief А function that differentiates by copying and modifying an already copied tree.
 * 
 * @param init_tree initial tree
 * @param diff_node node for recursion
 * @param root the root of the tree from which differentiation is performed
 * @param diff_var the variable by which differentiation is performed
 * @return Node* 
 */
Node* make_diff(Tree* init_tree, Node* diff_node, Node* root, const char* diff_var);

//========================================================================================
/**
 * @brief Auxiliary function for using the cL and cR define.
 * 
 * @param node_side node attachment side
 * @return Node* 
 */
Node* define_copy(Node* node_side);

//========================================================================================
/**
 * @brief Auxiliary function for using the dL and dR define.
 * 
 * @param node_side node attachment side
 * @return Node* 
 */
Node* define_make_diff(Tree* init_tree, Node* node_side, const char* diff_var);

//========================================================================================
/**
 * @brief A function to simplify the complexity of the tree.
 * 
 * @param init_tree initial tree
 * @param root the root of the tree from which simplification will begin
 * @return int 
 */
int simplification(Tree* init_tree, Node* root);

//========================================================================================

#endif // DIFF_FUNCTIONS_H
