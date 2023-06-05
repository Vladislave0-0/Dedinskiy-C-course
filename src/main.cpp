#include "./RecursiveDescent.h"
#include "../Graphics/GraphvizFunctions.h"
#include "./DiffFunctions.h"
#include "../Graphics/LatexFunctions.h"

//=============================================================================

int main()
{
    Tree* init_tree = init_tree_ctor("input.txt");
    if(init_tree == nullptr)
    {
        return ERROR_TREE_INIZIALIZATION;
    }

    init_tree->root = make_tree(init_tree);
    if(init_tree->root == nullptr)
    {
        init_tree_dtor(init_tree);

        return ERROR_FILE_SYNTAX;
    }

    FILE* tex_file = nullptr;
    const char* tex_filename = "TexExpression.tex";
    TEX_START(init_tree, tex_file, tex_filename);
    TEX_PRINT_VAR(init_tree, tex_file, "Variables processing.");

    
    simplification(init_tree, init_tree->root);
    parents_copy(init_tree->root);
    TEX_PRINT_TREE(tex_file, "The entered function.", init_tree, init_tree->root, "x", 0, VARIABLE);
    make_graph(init_tree->root, "GeneralTree.txt");
    Tree* numerical_tree = tree_ctor();
    numerical_tree->root = CREATE_NODE;
    node_copy(numerical_tree->root, init_tree->root);
    variable_substitution(init_tree, numerical_tree->root);
    func_like_eval(numerical_tree->root);
    TEX_PRINT_TREE(tex_file, "Variable substitution in entered function.", init_tree, numerical_tree->root, "x", 1, NUMBER);


    Tree* diff_tree = tree_ctor();
    diff_tree->root = CREATE_NODE;
    Node* root_to_free = diff_tree->root;
    diff_tree->root = make_diff(init_tree, diff_tree->root, init_tree->root, "x");
    childs_dtor(root_to_free);
    parents_copy(diff_tree->root);
    // TEX_PRINT_TREE(tex_file, "The first derivative of the variable x.", init_tree, diff_tree->root, "x", 1, VARIABLE);
    simplification(init_tree, diff_tree->root);
    TEX_PRINT_TREE(tex_file, "Simplified first derivative of the variable x.", init_tree, diff_tree->root, "x", 1, VARIABLE);
    make_graph(diff_tree->root, "DiffTree_var_x.txt");
    node_copy(numerical_tree->root, diff_tree->root);
    variable_substitution(init_tree, numerical_tree->root);
    func_like_eval(numerical_tree->root);
    TEX_PRINT_TREE(tex_file, "Variable substitution in first derivative of x.", init_tree, numerical_tree->root, "x", 1, NUMBER);


    diff_tree->root = make_diff(init_tree, diff_tree->root, init_tree->root, "y");
    parents_copy(diff_tree->root);
    // TEX_PRINT_TREE(tex_file, "The first derivative of the variable y.", init_tree, diff_tree->root, "y", 1, VARIABLE);
    simplification(init_tree, diff_tree->root);
    TEX_PRINT_TREE(tex_file, "Simplified first derivative of the variable y.", init_tree, diff_tree->root, "y", 1, VARIABLE);
    make_graph(diff_tree->root, "DiffTree_var_y.txt");
    node_copy(numerical_tree->root, diff_tree->root);
    variable_substitution(init_tree, numerical_tree->root);
    func_like_eval(numerical_tree->root);
    TEX_PRINT_TREE(tex_file, "Variable substitution in first derivative of y.", init_tree, numerical_tree->root, "y", 1, NUMBER);


    diff_tree->root = make_diff(init_tree, diff_tree->root, init_tree->root, "z");
    parents_copy(diff_tree->root);
    // TEX_PRINT_TREE(tex_file, "The first derivative of the variable z.", init_tree, diff_tree->root, "z", 1, VARIABLE);
    simplification(init_tree, diff_tree->root);
    TEX_PRINT_TREE(tex_file, "Simplified first derivative of the variable z.", init_tree, diff_tree->root, "z", 1, VARIABLE);
    make_graph(diff_tree->root, "DiffTree_var_z.txt");
    node_copy(numerical_tree->root, diff_tree->root);
    variable_substitution(init_tree, numerical_tree->root);
    func_like_eval(numerical_tree->root);
    TEX_PRINT_TREE(tex_file, "Variable substitution in first derivative of z.", init_tree, numerical_tree->root, "z", 1, NUMBER);


    other_tree_dtor(numerical_tree);
    TEX_END(tex_file, tex_filename, "SomeTexInfo");
    other_tree_dtor(diff_tree);
    init_tree_dtor(init_tree);
}
