#include "DiffFunctions.h"
#include "DSL.h"
#include "math.h"

#include "GraphvizFunctions.h"
//=============================================================================

static const double FloatConstant = 1E-6;

//=============================================================================

Node* make_diff(Node* diff_node, Node* root, const char* diff_var)
{
    if(root->type == OP)
    {
        if((root->val.op_code == '+') || (root->val.op_code == '-'))
        {
            if(root->val.op_code == '+')
            {
                diff_node->val.op_code = '+';   
            }

            if(root->val.op_code == '-')
            {
                diff_node->val.op_code = '-';   
            }

            diff_node->type = OP;
            diff_node->left_child  = CREATE_NODE;
            diff_node->right_child = CREATE_NODE;

            diff_node->left_child  = make_diff(diff_node->left_child, root->left_child, diff_var);
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            return diff_node;
        }

        else if(root->val.op_code == '*')
        {
            diff_node->val.op_code = '+';
            diff_node->type = OP;
        
            diff_node->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child = MUL_NODE(nullptr, nullptr);

            diff_node->left_child->left_child   = CREATE_NODE;
            diff_node->left_child->right_child  = CREATE_NODE;
            diff_node->right_child->left_child  = CREATE_NODE;
            diff_node->right_child->right_child = CREATE_NODE;

            diff_node->left_child->left_child = make_diff(diff_node->left_child->left_child, root->left_child, diff_var);
            node_copy(diff_node->left_child->right_child, root->right_child);

            diff_node->right_child->left_child = make_diff(diff_node->right_child->left_child, root->right_child, diff_var);
            node_copy(diff_node->right_child->right_child, root->left_child);

            return diff_node;
        }

        else if(root->val.op_code == '/')
        {
            diff_node->val.op_code = '/';
            diff_node->type = OP;

            diff_node->left_child  = SUB_NODE(nullptr, nullptr);
            diff_node->right_child = DIV_NODE(nullptr, nullptr);

            diff_node->left_child->left_child   = MUL_NODE(nullptr, nullptr);
            diff_node->left_child->right_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child->left_child  = CREATE_NODE;
            diff_node->right_child->right_child = CREATE_NUM(2);
            node_copy(diff_node->right_child->left_child, root->right_child);

            diff_node->left_child->left_child->left_child   = CREATE_NODE; 
            diff_node->left_child->left_child->right_child  = CREATE_NODE;
            diff_node->left_child->right_child->left_child  = CREATE_NODE;
            diff_node->left_child->right_child->right_child = CREATE_NODE;
            diff_node->left_child->left_child->left_child = make_diff(diff_node->left_child->left_child->left_child, root->left_child, diff_var);
            node_copy(diff_node->left_child->left_child->right_child, root->right_child);
            diff_node->left_child->right_child->left_child = make_diff(diff_node->left_child->right_child->left_child, root->right_child, diff_var);
            node_copy(diff_node->left_child->right_child->right_child, root->left_child);

            return diff_node;
        }

        else if(root->val.op_code == '^')
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = POW_NODE(nullptr, nullptr);
            diff_node->right_child = ADD_NODE(nullptr, nullptr);

            diff_node->left_child->left_child  = CREATE_NODE; 
            diff_node->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->left_child, root->left_child);
            node_copy(diff_node->left_child->right_child, root->right_child);

            diff_node->right_child->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child->right_child = DIV_NODE(nullptr, nullptr);

            diff_node->right_child->left_child->left_child   = CREATE_NODE;
            diff_node->right_child->left_child->right_child  = LN_NODE(nullptr);
            diff_node->right_child->right_child->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child->right_child->right_child = CREATE_NODE;

            diff_node->right_child->left_child->left_child = make_diff(diff_node->right_child->left_child->left_child, root->right_child, diff_var);
            node_copy(diff_node->right_child->right_child->right_child, root->left_child);

            diff_node->right_child->left_child->right_child->right_child = CREATE_NODE;
            diff_node->right_child->right_child->left_child->left_child  = CREATE_NODE;
            diff_node->right_child->right_child->left_child->right_child = CREATE_NODE;


            node_copy(diff_node->right_child->left_child->right_child->right_child, root->left_child);
            node_copy(diff_node->right_child->right_child->left_child->left_child, root->right_child);
            diff_node->right_child->right_child->left_child->right_child = make_diff(diff_node->right_child->right_child->left_child->right_child, root->left_child, diff_var);

            return diff_node;
        }

    }

    else if(root->type == NUM)
    {
        diff_node->type = NUM;
        diff_node->val.number = 0;

        return diff_node;
    }

    else if(root->type == VAR)
    {
        if(strcmp(root->val.var, diff_var) == 0)
        {
            diff_node->type = NUM;
            diff_node->val.number = 1;

            return diff_node;
        }

        else
        {
            diff_node->type = NUM;
            diff_node->val.number = 0;

            return diff_node;
        }
    }

    else if(root->type == FUNC)
    {
        if(strcmp(root->val.var, "sqrt") == 0)
        {
            diff_node->val.op_code = '/';
            diff_node->type = OP;

            diff_node->left_child = CREATE_NODE;
            diff_node->right_child = MUL_NODE(nullptr, nullptr);
            diff_node->left_child = make_diff(diff_node->left_child, root->right_child, diff_var);


            diff_node->right_child->left_child = CREATE_NUM(2);
            diff_node->right_child->right_child = SQRT_NODE(nullptr);

            diff_node->right_child->right_child->right_child = CREATE_NODE;
            node_copy(diff_node->right_child->right_child->right_child, root->right_child);

            return diff_node;
        }

        if(strcmp(root->val.var, "sin") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child = COS_NODE(nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "cos") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->left_child  = CREATE_NUM(-1);
            diff_node->left_child->right_child = SIN_NODE(nullptr);


            diff_node->left_child->right_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "tg") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = POW_NODE(nullptr, nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->left_child  = COS_NODE(nullptr);
            diff_node->left_child->right_child = CREATE_NUM(-2);
            diff_node->left_child->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->left_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "ctg") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->left_child  = CREATE_NUM(-1);
            diff_node->left_child->right_child = POW_NODE(nullptr, nullptr);

            diff_node->left_child->right_child->left_child  = SIN_NODE(nullptr);
            diff_node->left_child->right_child->right_child = CREATE_NUM(-2);

            diff_node->left_child->right_child->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child->left_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "arcsin") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = DIV_NODE(nullptr, nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);
        
            diff_node->left_child->left_child  = CREATE_NUM(1);
            diff_node->left_child->right_child = SQRT_NODE(nullptr);

            diff_node->left_child->right_child->right_child = SUB_NODE(nullptr, nullptr);

            diff_node->left_child->right_child->right_child->left_child  = CREATE_NUM(1);
            diff_node->left_child->right_child->right_child->right_child = POW_NODE(nullptr, nullptr);

            diff_node->left_child->right_child->right_child->right_child->left_child  = CREATE_NODE;
            diff_node->left_child->right_child->right_child->right_child->right_child = CREATE_NUM(2);

            node_copy(diff_node->left_child->right_child->right_child->right_child->left_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "arccos") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = DIV_NODE(nullptr, nullptr);
            diff_node->right_child = CREATE_NODE;


            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);
        
            diff_node->left_child->left_child  = CREATE_NUM(-1);
            diff_node->left_child->right_child = SQRT_NODE(nullptr);


            diff_node->left_child->right_child->right_child = SUB_NODE(nullptr, nullptr);

            diff_node->left_child->right_child->right_child->left_child  = CREATE_NUM(1);
            diff_node->left_child->right_child->right_child->right_child = POW_NODE(nullptr, nullptr);


            diff_node->left_child->right_child->right_child->right_child->left_child  = CREATE_NODE;
            diff_node->left_child->right_child->right_child->right_child->right_child = CREATE_NUM(2);

            node_copy(diff_node->left_child->right_child->right_child->right_child->left_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "arctg") == 0)
        {
            diff_node->val.op_code = '/';
            diff_node->type = OP;

            diff_node->left_child = CREATE_NODE;
            diff_node->right_child = SUB_NODE(nullptr, nullptr);
            diff_node->left_child = make_diff(diff_node->left_child, root->right_child, diff_var);

            diff_node->right_child->left_child  = CREATE_NUM(1);
            diff_node->right_child->right_child = POW_NODE(nullptr, nullptr);

            diff_node->right_child->right_child->left_child  = CREATE_NODE;
            diff_node->right_child->right_child->right_child = CREATE_NUM(2);


            node_copy(diff_node->right_child->right_child->left_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "arcctg") == 0)
        {
            diff_node->val.op_code = '/';
            diff_node->type = OP;

            diff_node->left_child  = MUL_NODE(nullptr, nullptr);
            diff_node->right_child = SUB_NODE(nullptr, nullptr);


            diff_node->left_child->left_child  = CREATE_NUM(-1);
            diff_node->left_child->right_child = CREATE_NODE;
            diff_node->left_child->right_child = make_diff(diff_node->left_child->right_child, root->right_child, diff_var);


            diff_node->right_child->left_child  = CREATE_NUM(1);
            diff_node->right_child->right_child = POW_NODE(nullptr, nullptr);

            diff_node->right_child->right_child->left_child  = CREATE_NODE;
            diff_node->right_child->right_child->right_child = CREATE_NUM(2);

            node_copy(diff_node->right_child->right_child->left_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "sh") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;
            
            diff_node->left_child  = CH_NODE(nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "ch") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;

            diff_node->left_child  = SH_NODE(nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "ln") == 0)
        {
            diff_node->val.op_code = '/';
            diff_node->type = OP;   

            diff_node->left_child = CREATE_NODE;
            diff_node->right_child = CREATE_NODE;
            diff_node->left_child = make_diff(diff_node->left_child, root->right_child, diff_var);
            node_copy(diff_node->right_child, root->right_child);

            return diff_node;
        }
        
        if(strcmp(root->val.var, "exp") == 0)
        {
            diff_node->val.op_code = '*';
            diff_node->type = OP;   

            diff_node->left_child  = EXP_NODE(nullptr);
            diff_node->right_child = CREATE_NODE;
            diff_node->right_child = make_diff(diff_node->right_child, root->right_child, diff_var);

            diff_node->left_child->right_child = CREATE_NODE;
            node_copy(diff_node->left_child->right_child, root->right_child);

            return diff_node;
        }
    }

    return diff_node;
}

//=============================================================================

void diff_tree_dtor(Tree* diff_tree)
{
    childs_dtor(diff_tree->root);

    free(diff_tree);
}

//=============================================================================

void node_copy(struct Node* diff_node, struct Node* root)
{
    diff_node->type   = root->type;
    diff_node->parent = root->parent;

    if(diff_node->type == NUM)
    {
        diff_node->val.number = root->val.number;
    }

    else if(diff_node->type == OP)
    {
        diff_node->val.op_code = root->val.op_code;
    }

    else if((diff_node->type == VAR) || (diff_node->type == FUNC))
    {
        diff_node->val.var = root->val.var;
    }

    if(root->left_child != nullptr)
    {
        diff_node->left_child = CREATE_NODE;

        node_copy(diff_node->left_child, root->left_child);
    }

    else
    {
        diff_node->left_child = nullptr;
    }

    if(root->right_child != nullptr)
    {
        diff_node->right_child = CREATE_NODE;

        node_copy(diff_node->right_child, root->right_child);
    }

    else
    {
        diff_node->right_child = nullptr;
    }
}

//=============================================================================

void parents_copy(struct Node* root)
{
    if(root == nullptr)
    {
        return;
    }

    if(root->left_child != nullptr)
    {
        root->left_child->parent = root;
        parents_copy(root->left_child);
    }

    if(root->right_child != nullptr)
    {
        root->right_child->parent = root;
        parents_copy(root->right_child);
    }
}

//=============================================================================

void simplification(Node* root)
{
    if(root == nullptr)
    {
        return;
    }
    if(root->left_child != nullptr)
    {
        simplification(root->left_child);
    }

    if(root->right_child != nullptr)
    {
        simplification(root->right_child);
    }

    if(root->type == OP)
    {
        if(root->left_child->type == NUM && root->right_child->type == NUM)
        {
            root->type = NUM;

            if(root->val.op_code == '+')
            {
                root->val.number = root->left_child->val.number + root->right_child->val.number;
            }

            else if(root->val.op_code == '-')
            {
                root->val.number = root->left_child->val.number - root->right_child->val.number;
            }

            else if(root->val.op_code == '*')
            {
                root->val.number = root->left_child->val.number * root->right_child->val.number;
            }

            else if(root->val.op_code == '/')
            {
                if(float_comparison(root->right_child->val.number, 0) == EQUAL)
                {
                    printf("ДЕЛЕНИЕ НА НУЛЬ!");
                    return;
                }

                root->val.number = root->left_child->val.number / root->right_child->val.number;
            }

            else if(root->val.op_code == '^')
            {
                if(float_comparison(root->left_child->val.number, 0) == UNDER)
                {
                    printf("Для действительных чисел нельзя производить возведение в степень отрицательного числа!\n");

                    return;
                }

                root->val.number = pow(root->left_child->val.number, root->right_child->val.number);
            }

            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }

        else if(((root->left_child->type != NUM)  && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 0) == EQUAL)  && (root->val.op_code == '*')) ||
                ((root->right_child->type != NUM) && (root->left_child->type == NUM)  && (float_comparison(root->left_child->val.number, 0)  == EQUAL)  && (root->val.op_code == '*')))
        {
            root->type = NUM;
            root->val.number = 0;
            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }
        
        else if((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 1) == EQUAL) && (root->val.op_code == '*'))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->left_child->parent = root->parent;
                    root->parent->left_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->left_child->parent  = root->parent;
                    root->parent->right_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                Node* tree_to_dtor = root->left_child;

                node_copy(root, root->left_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;

            }
        }

        else if((root->right_child->type != NUM) && (root->left_child->type == NUM) && (float_comparison(root->left_child->val.number, 1) == EQUAL) && (root->val.op_code == '*'))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->left_child);
                root->left_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->right_child->parent = root->parent;
                    root->parent->left_child  = root->right_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->right_child->parent = root->parent;
                    root->parent->right_child = root->right_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->left_child);
                root->left_child = nullptr;

                Node* tree_to_dtor = root->right_child;

                node_copy(root, root->right_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;
            }
        }

        else if((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 1) == EQUAL) && (root->val.op_code == '/'))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->left_child->parent = root->parent;
                    root->parent->left_child = root->left_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->left_child->parent  = root->parent;
                    root->parent->right_child = root->right_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                Node* tree_to_dtor = root->left_child;

                node_copy(root, root->left_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;
            }
        }

        else if((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 0) == EQUAL) && ((root->val.op_code == '-') || (root->val.op_code == '+')))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->left_child->parent = root->parent;
                    root->parent->left_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->left_child->parent  = root->parent;
                    root->parent->right_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                Node* tree_to_dtor = root->left_child;

                node_copy(root, root->left_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;
            }
        }

        else if((root->left_child->type == NUM) && (root->right_child->type != NUM) && (float_comparison(root->left_child->val.number, 0) == EQUAL)  && (root->val.op_code == '+'))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->left_child);
                root->left_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->right_child->parent = root->parent;
                    root->parent->left_child  = root->right_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->right_child->parent = root->parent;
                    root->parent->right_child = root->right_child;

                    root->parent      = nullptr;
                    root->right_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->left_child);
                root->left_child = nullptr;

                Node* tree_to_dtor = root->right_child;

                node_copy(root, root->right_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;
            }
        }

        else if((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 1) == EQUAL)  && (root->val.op_code == '^'))
        {
            if(root->parent != nullptr)
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                if(root->parent->left_child == root)
                {
                    root->left_child->parent = root->parent;
                    root->parent->left_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }

                else if(root->parent->right_child == root)
                {
                    root->left_child->parent  = root->parent;
                    root->parent->right_child = root->left_child;

                    root->parent     = nullptr;
                    root->left_child = nullptr;

                    childs_dtor(root);
                }
            }

            else
            {
                childs_dtor(root->right_child);
                root->right_child = nullptr;

                Node* tree_to_dtor = root->left_child;

                node_copy(root, root->left_child);

                childs_dtor(tree_to_dtor);
                tree_to_dtor = nullptr;
            }
        }

        else if(((root->left_child->type == NUM) && (root->right_child->type != NUM) && (float_comparison(root->left_child->val.number, 1) == EQUAL)  && (root->val.op_code == '^')) ||
                ((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->left_child->val.number, 0) == EQUAL)  && (root->val.op_code == '^')))
        {
            root->type = NUM;
            root->val.number = 1;
            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }

        else if((root->left_child->type == NUM) && (root->right_child->type != NUM) && (float_comparison(root->left_child->val.number, 0) == EQUAL)  && (root->val.op_code == '^'))
        {
            root->type = NUM;
            root->val.number = 0;
            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }
    }
}

//===========================================================================

ComparisonResult float_comparison(const double x1, const double x2)
{
    if (fabs(x1 - x2) <= FloatConstant)
        return EQUAL;

    else 
        return ((x1-x2) > FloatConstant) ? OVER : UNDER;
}

//===========================================================================
