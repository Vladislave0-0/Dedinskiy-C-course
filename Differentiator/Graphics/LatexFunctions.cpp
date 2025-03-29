#include "./LatexFunctions.h"

//===================================================================================================================================

void tex_head(FILE* tex_file)
{
    fprintf(tex_file, "\\documentclass{article}\n");
    fprintf(tex_file, "\\usepackage[utf8]{inputenc}\n");
    fprintf(tex_file, "\\usepackage{graphicx}\n");
    fprintf(tex_file, "\\usepackage[10pt]{extsizes}\n");
    fprintf(tex_file, "\\usepackage{amsmath, amsfonts, amssymb, amsthm, mathtools}\n");
    fprintf(tex_file, "\\usepackage{geometry}\n\\geometry{\n\ta4paper,\n\tleft = 20 mm,\n\ttop = 20 mm,\n}\n\n");

    fprintf(tex_file, "\\title{\\vspace{-1.0cm}\\textbf{Taking the derivative of a function.}}\n");
    fprintf(tex_file, "\\author{Vlad Lazar aka Properdosik and god of recursions.}\n\n");
    fprintf(tex_file, "\\begin{document}\n");
    fprintf(tex_file, "\\maketitle\n");
    fprintf(tex_file, "\\section{Introduction}\n");
    fprintf(tex_file, "\\textit{Rest in peace, my brothers, for it is coming...}\n");
}

//===================================================================================================================================

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
            if(root->parent != nullptr)
            {
                if((root->parent->type == FUNC) || ((root->parent->type == OP) && (root->parent->val.op_code == '/')))
                {
                    tex_print_tree(root->left_child, tex_file, section);
                    fprintf(tex_file, " + ");
                    tex_print_tree(root->right_child, tex_file, section);
                }

                else
                {
                    fprintf(tex_file, "(");
                    tex_print_tree(root->left_child, tex_file, section);
                    fprintf(tex_file, " + ");
                    tex_print_tree(root->right_child, tex_file, section);
                    fprintf(tex_file, ")");
                }
            }

            else
            {
                tex_print_tree(root->left_child, tex_file, section);
                fprintf(tex_file, " + ");
                tex_print_tree(root->right_child, tex_file, section);
            }
        }

        if(root->val.op_code == '-')
        {
            if(root->parent != nullptr)
            {
                fprintf(tex_file, "(");
                tex_print_tree(root->left_child, tex_file, section);
                fprintf(tex_file, " - ");
                tex_print_tree(root->right_child, tex_file, section);
                fprintf(tex_file, ")");
            }

            else
            {
                tex_print_tree(root->left_child, tex_file, section);
                fprintf(tex_file, " - ");
                tex_print_tree(root->right_child, tex_file, section);
            }
        }

        if(root->val.op_code == '*')
        {
            tex_print_tree(root->left_child, tex_file, section);
            fprintf(tex_file, " \\cdot ");
            tex_print_tree(root->right_child, tex_file, section);
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
        if(root->parent != nullptr)
        {
            if((float_comparison(root->val.number, 0) != UNDER) || (root->parent->val.op_code == '/'))
            {
                fprintf(tex_file, "%g", root->val.number);
            }

            else
            {
                fprintf(tex_file, "(%g)", root->val.number);
            }
        }

        else
        {
            fprintf(tex_file, "%g", root->val.number);
        }
    }
}

//===================================================================================================================================

void tex_print_var(Tree* tree, FILE* fileptr)
{
    if(tree->vars_num == 0)
    {
        fprintf(fileptr, "\\textit{No variables were found when reading the file. The final substitution "
                         "of variables will not be performed.}\\\n");

        return;
    }

    fprintf(fileptr, "Variables that you entered during initialization:\\\\\n");

    for(int i = 0; i < tree->vars_num; i++)
    {
        fprintf(fileptr, "$%s = %g$\n", tree->vars_arr[i].text, tree->vars_arr[i].value);

        if(i < tree->vars_num - 1)
        {
            fprintf(fileptr, "\\\\");
        }
    }
}

//===================================================================================================================================

void func_for_tex_define(FILE* file, const char* section, Tree* tree, const char* derivative_var, int derivative_number, int print_type)
{
    fprintf(file, "\n\\section{%s}\n", section);                                            
    fprintf(file, "$");                                                                     
                                                                                            
    if(derivative_number != 0)                                                              
    {                                                                                       
        if(derivative_number == 1)                                                          
        {                                                                                   
            fprintf(file, "\\frac{\\partial ");                                             
        }                                                                                   
                                                                                            
        else                                                                                
        {                                                                                   
            fprintf(file, "\\frac{\\partial^%d ", derivative_number);                       
        }                                                                                   
    }                                                                                       
                                                                                            
    fprintf(file, "f");                                                                     
    if(tree->vars_num != 0)                                                                 
    {                                                                                       
        fprintf(file, "(");                                                                 
                                                                                            
        if(print_type == 1)                                                 
        {                                                                                   
            for(int i = 0; i < tree->vars_num; i++)                                         
            {                                                                               
                fprintf(file, "%g", tree->vars_arr[i].value);                               
                if(i != tree->vars_num - 1)                                                 
                {                                                                           
                    fprintf(file, ",\\ ");                                                    
                }                                                                           
            }                                                                               
        }                                                                                   
                                                                                            
        else                                                                                
        {                                                                                   
            for(int i = 0; i < tree->vars_num; i++)                                         
            {                                                                               
                fprintf(file, "%s", tree->vars_arr[i].text); 

                if(i != tree->vars_num - 1)                                                 
                {                                                                           
                    fprintf(file, ",\\ ");                                                    
                }                                                                           
            }                                                                               
        }  

        fprintf(file, ")");                                                                 
    }                                                                                       
                                                                                            
    if(derivative_number != 0)                                                              
    {                                                                                       
        if(derivative_number == 1)                                                          
        {                                                                                   
            fprintf(file, "}{\\partial %s}", derivative_var);                               
        }                                                                                   
                                                                                            
        else                                                                                
        {                                                                                   
            fprintf(file, "}{\\partial%s^%d}", derivative_var, derivative_number);          
        }                                                                                   
    }                                                                                       
                                                                                            
    fprintf(file, " = ");                                                                   
}

//===================================================================================================================================

void delete_logs(const char* tex_filename, const char* terminal_output)
{
    char pdf_latex_command[60] = "pdflatex ./Output/";  
    char rm_rf_aux[60]         = "rm -rf ";               
    char rm_rf_log[60]         = "rm -rf ";
    char rm_rf_info[60]        = "rm -rf ";
    char no_ext_filename[60]   = "";
    strncpy(no_ext_filename, tex_filename, strlen(tex_filename) - 3);

    strcat(pdf_latex_command, tex_filename);                   
    strcat(pdf_latex_command, " > ");  
    strcat(pdf_latex_command, terminal_output);
    strcat(pdf_latex_command, " 2>&1");

    strcat(rm_rf_aux, no_ext_filename);                  
    strcat(rm_rf_aux, "aux");   
                      
    strcat(rm_rf_log, no_ext_filename);                   
    strcat(rm_rf_log, "log");    

    strcat(rm_rf_info, terminal_output);

    system(pdf_latex_command);                                 
    system(rm_rf_aux);                                 
    system(rm_rf_log);           
    system(rm_rf_info);              
}
