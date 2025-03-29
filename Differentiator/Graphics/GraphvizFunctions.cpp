#include "./GraphvizFunctions.h"

//=====================================================================================================================

#define PRINT_NUM                                                                                           \
        fprintf(dotfile, "\tnode_%p [style = \"filled\", fillcolor = skyblue, shape = Mrecord, label = "    \
                         "\"{{<f1> %p}| {type: NUM | value = %lf} | {<f2>%p | <f3> %p}}\"];\n",             \
                          root, root, root->val.number, root->right_child, root->right_child);              \


#define PRINT_VAR                                                                                           \
        fprintf(dotfile, "\tnode_%p [style = \"filled\", fillcolor = red, shape = Mrecord, label = "        \
                         "\"{{<f1> %p}| {type: VAR | value = %s} | {<f2>%p | <f3> %p}}\"];\n",              \
                          root, root, root->val.var, root->left_child, root->right_child);                  \


#define PRINT_FUNC                                                                                          \
        fprintf(dotfile, "\tnode_%p [style = \"filled\", fillcolor = green, shape = Mrecord, label = "      \
                         "\"{{<f1> %p}| {type: FUNC | value = %s} | {<f2>%p | <f3> %p}}\"];\n",             \
                          root, root, root->val.var, root->left_child, root->right_child);                  \


#define PRINT_OP                                                                                            \
        fprintf(dotfile, "\tnode_%p [style = \"filled\", fillcolor = yellow, shape = Mrecord, label = "     \
                         "\"{{<f1> %p}| {type: OP | value = %c} | {<f2>%p | <f3> %p}}\"];\n",               \
                          root, root, root->val.op_code, root->left_child, root->right_child);              \


#define PRINT_CHILD                                                                                 \
        if(root->left_child != nullptr)                                                             \
        {                                                                                           \
            fprintf(dotfile, "\tnode_%p:<f2>:s -> node_%p:<f1>:n;\n", root, root->left_child);      \
        }                                                                                           \
                                                                                                    \
        if(root->right_child != nullptr)                                                            \
        {                                                                                           \
            fprintf(dotfile, "\tnode_%p:<f3>:s -> node_%p:<f1>:n;\n", root, root->right_child);     \
        }                                                                                           \

//=====================================================================================================================

void make_graph(Node* root, const char* filename) 
{
    char path[30] = "./Output/";                    
    strcat(path, filename);     
    FILE* dotfile = fopen(path, "w");

    if(dotfile == nullptr)
    {
        printf(RED "\nIn function %s at %s(%u):\nError code: %d. Check file \"Tree.h\" to decipher "
                   "the error code.\n\n" RESET, __PRETTY_FUNCTION__, __FILE__, __LINE__, ERROR_OPEN_GRAPHVIZ_FILE);       

        return;
    }

    fprintf(dotfile, "digraph tree\n");
    fprintf(dotfile, "{\n");
    fprintf(dotfile, "\trankdir = TB;\n");
    fprintf(dotfile, "\tsplines = false;\n\n");

    print_dot_tree(root, dotfile);
    fprintf(dotfile, "}\n\n");
    fclose(dotfile);


    char dot_command[70] = "dot ";
    char new_file_ext[30] = {};
    strcat(dot_command, path);
    strcat(dot_command, " -Tpng -o ");
    strcat(dot_command, "./Output/");
    for(size_t i = 0; i < strlen(filename) - 3; i++)
    {
        new_file_ext[i] = filename[i];
    }
    strcat(new_file_ext, "png");
    strcat(dot_command, new_file_ext);                

    system(dot_command);
}

//=====================================================================================================================

void print_dot_tree(Node* root, FILE* dotfile)
{
    if(root->type == NUM)                                                                                                                                                                                                                                   
    {   
        PRINT_NUM;
    }  

    else if(root->type == VAR)                                                                                                                                                                                                        
    {                    
        PRINT_VAR;        
    }                                                                                                                                                                                                                                                     
                                                                                                                                                                                                                                                            
    else if(root->type == OP)                                                                                                                                                                                                                               
    { 
        PRINT_OP;    
        PRINT_CHILD;                                                                                                                                                                                                                                                 
    }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
    
    else if(root->type == FUNC)    
    {
        PRINT_FUNC;
        PRINT_CHILD;
    }                                                                                                                                                                                                                                         

    if(root->left_child != nullptr)
    {
        print_dot_tree(root->left_child, dotfile);
    }

    if(root->right_child != nullptr)
    {
        print_dot_tree(root->right_child, dotfile);
    }
}
