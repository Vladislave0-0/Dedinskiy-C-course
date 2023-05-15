#include "LatexFunctions.h"


//==============================================================================

void tex_head(FILE* tex_file)
{
    fprintf(tex_file, "\\documentclass{article}\n");
    fprintf(tex_file, "\\usepackage[utf8]{inputenc}\n");
    fprintf(tex_file, "\\usepackage{graphicx}\n");
    fprintf(tex_file, "\\usepackage[14pt]{extsizes}\n");
    fprintf(tex_file, "\\usepackage{amsmath, amsfonts, amssymb, amsthm, mathtools}\n");
    fprintf(tex_file, "\\usepackage{geometry}\n\\geometry{\na4paper,\nleft = 20 mm,\ntop = 20 mm,\n}\n\n");

    fprintf(tex_file, "\\title{\\vspace{-1.0cm}\\textbf{Taking the derivative of a function.}}\n");
    fprintf(tex_file, "\\author{Vlad Lazar aka Properdosik and god of recursions.}\n\n");
    fprintf(tex_file, "\\begin{document}\n");
    fprintf(tex_file, "\\maketitle\n");
    fprintf(tex_file, "\\section{Introduction}\n");
    fprintf(tex_file, "\\textit{Rest in peace, my brothers, for it is coming...}\n");
}

void tex_print_tree(Node* root, FILE* tex_file, const char* section)
{
    if(root->type == FUNC)
    {
        fprintf(tex_file, "%s(", root->val.var);
        tex_print_tree(root->right_child, tex_file, section);
        fprintf(tex_file, ")");
    }

    if(root->type == OP)
    {
        if(root->val.op_code == '+')
        {
            fprintf(tex_file, "(");
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, " + ");
            tex_print_tree(root->right_child, tex_file, section);
            fprintf(tex_file, ")");
        }

        if(root->val.op_code == '-')
        {
            fprintf(tex_file, "(");
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, " - ");
            tex_print_tree(root->right_child, tex_file, section);
            fprintf(tex_file, ")");
        }

        if(root->val.op_code == '*')
        {
            fprintf(tex_file, "[");
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, " \\cdot ");
            tex_print_tree(root->right_child, tex_file, section);
            fprintf(tex_file, "]");
        }

        if(root->val.op_code == '/')
        {
            fprintf(tex_file, "\\frac{");   
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, "}{");
            tex_print_tree(root->right_child, tex_file, section);
            fprintf(tex_file, "}");
        }

        if(root->val.op_code == '^')
        {
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, "^{");
            tex_print_tree(root->right_child, tex_file, section);
            fprintf(tex_file, "}");
        }
    }

    else if(root->type == VAR)
    {
        fprintf(tex_file, "%s", root->val.var);
    }

    else if(root->type == NUM)
    {
        char num_in_str[30] = {};
        sprintf(num_in_str, "%lf", root->val.number);
        size_t num_len = strlen(num_in_str);

        size_t i = num_len - 1;
        for(; num_in_str[i] != '.' && num_in_str[i] == '0'; i--)
            ;

        if(num_in_str[i] == '.')
        {
            i--;
        }

        char new_num_in_str[30] = {};
        strncpy(new_num_in_str, num_in_str, i + 1);

        if(new_num_in_str[0] == '-')
        {
            if(root->parent != nullptr)
            {
                if(root->parent->right_child == root)
                {
                    fprintf(tex_file, "(");
                    fprintf(tex_file, "%s", new_num_in_str);
                    fprintf(tex_file, ")");
                }

                else if(root->parent->left_child)
                {
                    fprintf(tex_file, "%s", new_num_in_str);
                }
            }

            else
            {
                fprintf(tex_file, "%s", new_num_in_str);
            }
        }

        else
        {
            fprintf(tex_file, "%s", new_num_in_str);
        }
    }
}

void tex_print_var(Tree* tree, FILE* fileptr)
{
    if(tree->vars_num == 0)
    {
        fprintf(fileptr, "\\textit{No variables were found when reading the file. The final substitution of variables will not be performed.}\\\n");

        return;
    }

    fprintf(fileptr, "Variables that you entered during initialization:\\\\\n");

    for(int i = 0; i < tree->vars_num; i++)
    {

        char num_in_str[30] = {};
        sprintf(num_in_str, "%lf", tree->vars_arr[i].value);
        size_t num_len = strlen(num_in_str);

        size_t j = num_len - 1;
        for(; num_in_str[j] != '.' && num_in_str[j] == '0'; j--)
            ;

        if(num_in_str[j] == '.')
        {
            j--;
        }

        char new_num_in_str[30] = {};
        strncpy(new_num_in_str, num_in_str, j + 1);

        fprintf(fileptr, "$%s = %s$\n", tree->vars_arr[i].text, new_num_in_str);

        if(i < tree->vars_num - 1)
        {
            fprintf(fileptr, "\\\\");
        }
    }
}
