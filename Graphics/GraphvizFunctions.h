#ifndef GRAPHVIZ_FUNCTIONS_H
#define GRAPHVIZ_FUNCTIONS_H

//=======================================================

#include "../src/Tree.h"

//=======================================================

void make_graph(Node* root, const char* filename);

//=======================================================

void print_dot_tree(Node* root, FILE* dotfile);

//=======================================================

#endif //GRAPHVIZ_FUNCTIONS_H
