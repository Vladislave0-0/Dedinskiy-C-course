#ifndef LATEX_FUNCTIONS_H
#define LATEX_FUNCTIONS_H


#define TEX_PRINT_TREE(root, file, section)                                     \
        fprintf(file, "\n\\section{%s}\n$", section);                           \
        tex_print_tree(root, file, section);                                    \
        fprintf(file, "$\n");                                                   \
        

#define TEX_PRINT_VAR(tree, file, section)                                              \
        fprintf(file, "\n\\section{%s}\n", section);                                    \
        tex_print_var(tree, file);                                                      \

        
//==============================================================================

#include "Tree.h"
#include <string.h>

//==============================================================================

void tex_head(FILE* tex_file);

//==============================================================================

void tex_print_tree(Node* root, FILE* tex_file, const char* section);

//==============================================================================

void tex_print_var(Tree* tree, FILE* fileptr);

//==============================================================================

#endif //LATEX_FUNCTIONS_H
