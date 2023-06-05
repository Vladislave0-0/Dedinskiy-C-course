#ifndef LATEX_FUNCTIONS_H
#define LATEX_FUNCTIONS_H

//======================================================================================================================================

#include "../src/Tree.h"

//======================================================================================================================================

#define TEX_PRINT_TREE(file, section, tree, root, derivative_var, derivative_number, print_type)        \
        func_for_tex_define(file, section, tree, derivative_var, derivative_number, print_type);        \
        tex_print_tree(root, file, section);                                                            \
        fprintf(file, "$\n");                                                                           \
        

#define TEX_PRINT_VAR(tree, file, section)                      \
        fprintf(file, "\n\\section{%s}\n", section);            \
        tex_print_var(tree, file);                              \


#define TEX_START(init_tree, file, filename)            \
        char path[30] = "./Output/";                    \
        strcat(path, filename);                         \
        file = file_open(init_tree, path);              \
        tex_head(file);                                 \


#define TEX_END(file, tex_filename, terminal_output)            \
        fprintf(file, "\n\\end{document}\n");                   \
        fclose(file);                                           \
        delete_logs(tex_filename, terminal_output)              \

//======================================================================================================================================

// constants for selecting a printout:
const int NUMBER   = 1;      // A tree converted to a number (numerical tree).
const int VARIABLE = 2;      // A tree that has variables or functions.

//======================================================================================================================================
/**
 * @brief Output to .tex header file, custom packages, output settings.
 * 
 * @param tex_file .tex file
 */
void tex_head(FILE* tex_file);

//======================================================================================================================================
/**
 * @brief Output of the tree to a .tex file, taking into account the correct, but not redundant, bracket structure.
 * 
 * @param root the root of the tree from which the printout begins
 * @param tex_file .tex file
 * @param section title when printing a fragment of the tree for greater clarity
 */
void tex_print_tree(Node* root, FILE* tex_file, const char* section);

//======================================================================================================================================
/**
 * @brief Printout of variables entered by the user into the terminal.
 * 
 * @param tree initial tree
 * @param fileptr .tex file
 */
void tex_print_var(Tree* tree, FILE* fileptr);

//======================================================================================================================================
/**
 * @brief Auxiliary function for the operation of the define TEX_PRINT_TREE.
 * 
 * @param file .tex file
 * @param section title when printing a fragment of the tree for greater clarity
 * @param tree initial tree
 * @param derivative_var the variable by which differentiation occurred
 * @param derivative_number which derivative was taken in the account
 * @param print_type constants for selecting a printout (check LatexFunctions.h(35))
 */
void func_for_tex_define(FILE* file, const char* section, Tree* tree, const char* derivative_var, int derivative_number, int print_type);

//======================================================================================================================================
/**
 * @brief Compiling a latex document and deleting unnecessary log files.
 * 
 * @param tex_filename .tex file name
 * @param terminal_output log files named like terminal_output
 */
void delete_logs(const char* tex_filename, const char* terminal_output);

//======================================================================================================================================

#endif //LATEX_FUNCTIONS_H
