#ifndef LATEX_FUNCTIONS_H
#define LATEX_FUNCTIONS_H

//======================================================================================================================================

#include "../src/Tree.h"

//======================================================================================================================================

#define TEX_PRINT_TREE(file, section, tree, root, derivative_var, derivative_number, print_type)        \
        func_for_texdef(file, section, tree, derivative_var, derivative_number, print_type);            \
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

const int NUMBER   = 1;
const int VARIABLE = 2;

//======================================================================================================================================

void tex_head(FILE* tex_file);

//======================================================================================================================================

void tex_print_tree(Node* root, FILE* tex_file, const char* section);

//======================================================================================================================================

void tex_print_var(Tree* tree, FILE* fileptr);

//======================================================================================================================================

void func_for_texdef(FILE* file, const char* section, Tree* tree, const char* derivative_var, int derivative_number, int print_type);

//======================================================================================================================================

void delete_logs(const char* tex_filename, const char* terminal_output);

//======================================================================================================================================

#endif //LATEX_FUNCTIONS_H
