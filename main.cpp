#include "Tree.h"
#include "RecursiveDescent.h"
#include "GraphvizFunctions.h"
#include "DiffFunctions.h"
#include "LatexFunctions.h"
#include "DSL.h"

//=============================================================================

int main()
{
    FILE* tex_file = fopen("TexExpression.tex", "w");
    tex_head(tex_file);
    Tree* init_tree = tree_ctor();
    file_processing(init_tree, "tree_file.txt");
    variables_processing(init_tree);
    TEX_PRINT_VAR(init_tree, tex_file, "Variables processing.");


    init_tree->root = make_tree(init_tree);
    parents_copy(init_tree->root);
    TEX_PRINT_TREE(init_tree->root, tex_file, "Initial tree.");
    simplification(init_tree->root);
    TEX_PRINT_TREE(init_tree->root, tex_file, "Simplified initial tree.");
    make_graph(init_tree->root, "GeneralTree.txt");


    Tree* diff_tree = tree_ctor();
    diff_tree->root = CREATE_NODE;
    make_diff(diff_tree->root, init_tree->root, "x");
    TEX_PRINT_TREE(diff_tree->root, tex_file, "Differentiated tree.");
    parents_copy(diff_tree->root);
    simplification(diff_tree->root);
    TEX_PRINT_TREE(diff_tree->root, tex_file, "Simplified differentiated tree.");
    make_graph(diff_tree->root, "DiffTree.txt");


    // Tree* numerical_tree = tree_ctor();
    // numerical_tree->root = CREATE_NODE;
    // node_copy(numerical_tree->root, diff_tree->root);
    // variable_substitution(init_tree, numerical_tree->root);
    // TEX_PRINT_TREE(numerical_tree->root, tex_file, "Variable substitution.");
    // make_graph(numerical_tree->root, "numerical_tree.txt");
    // diff_tree_dtor(numerical_tree);


    fprintf(tex_file, "\n\\end{document}");
    diff_tree_dtor(diff_tree);
    tree_dtor(init_tree);
}

//dot graphviz.txt -Tpng -o tree.png
//pdflatex TexExpression.tex > nul 2>&1
