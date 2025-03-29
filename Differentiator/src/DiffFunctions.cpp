#include <math.h>

#include "./DiffFunctions.h"

//==========================================================================================================================================

Node* make_diff(Tree* init_tree, Node* diff_node, Node* root, const char* diff_var)
{
    if(root->type == OP)
    {
        switch(root->val.op_code)
        {
            case('+'): return Add(dL, dR);
            case('-'): return Sub(dL, dR);
            case('*'): return Add(Mul(dL, cR), Mul(dR, cL));
            case('/'): return Div(Sub(Mul(dL, cR), Mul(dR, cL)), Pow(cR, CREATE_NUM(2)));
            case('^'): return Mul(Pow(cL, cR), Add(Mul(dR, LN_NODE(cL)), Div(Mul(cR, dL), cL)));

            default:
            {
                printf(RED "UNKNOWN OPERATOR IN FUNC MAKE_DIFF!\n\n" RESET);
                break;
            }
        }
    }

    else if(root->type == NUM)
    {
        return CREATE_NUM(0);
    }

    else if(root->type == VAR)
    {
        if(strcmp(root->val.var, diff_var) == 0)
        {
            return CREATE_NUM(1);
        }

        else
        {
            return CREATE_NUM(0);
        }
    }

    else if(root->type == FUNC)
    {
        if(!strcmp(root->val.var, "sqrt"))      return Div(dR, Mul(CREATE_NUM(2), SQRT_NODE(cR)));

        if(!strcmp(root->val.var, "sin"))       return Mul(COS_NODE(cR), dR);
        
        if(!strcmp(root->val.var, "cos"))       return Mul(Mul(CREATE_NUM(-1), SIN_NODE(cR)), dR);
        
        if(!strcmp(root->val.var, "tg"))        return Mul(Div(CREATE_NUM(1), Pow(COS_NODE(cR), CREATE_NUM(2))), dR);
        
        if(!strcmp(root->val.var, "ctg"))       return Mul(Div(CREATE_NUM(-1), Pow(SIN_NODE(cR), CREATE_NUM(2))), dR);
        
        if(!strcmp(root->val.var, "arcsin"))    return Mul(Div(CREATE_NUM(1), SQRT_NODE(Sub(CREATE_NUM(1), Pow(cR, CREATE_NUM(2))))), dR);
        
        if(!strcmp(root->val.var, "arccos"))    return Mul(Div(CREATE_NUM(-1), SQRT_NODE(Sub(CREATE_NUM(1), Pow(cR, CREATE_NUM(2))))), dR);
        
        if(!strcmp(root->val.var, "arctg"))     return Div(dR, Add(CREATE_NUM(1), Pow(cR, CREATE_NUM(2))));
        
        if(!strcmp(root->val.var, "arcctg"))    return Div(Mul(CREATE_NUM(-1), dR), Add(CREATE_NUM(1), Pow(cR, CREATE_NUM(2))));
        
        if(!strcmp(root->val.var, "sh"))        return Mul(CH_NODE(cR), dR);
        
        if(!strcmp(root->val.var, "ch"))        return Mul(SH_NODE(cR), dR);
        
        if(!strcmp(root->val.var, "ln"))        return Div(dR, cR);
        
        if(!strcmp(root->val.var, "exp"))       return Mul(EXP_NODE(cR), dR);
    }

    return diff_node;
}

//==========================================================================================================================================

Node* define_copy(Node* node_side)
{                      
    Node* cur_node = CREATE_NODE;  
    node_copy(cur_node, node_side); 

    return cur_node; 
}

//==========================================================================================================================================

Node* define_make_diff(Tree* init_tree, Node* node_side, const char* diff_var)
{
    Node* cur_node = CREATE_NODE;
    Node* cur_node1 = cur_node;

    cur_node = make_diff(init_tree, cur_node, node_side, diff_var);
    Node* cur_node2 = cur_node;

    if(cur_node1 != cur_node2)      //| the pointer changes after differentiation and the first call may be lost
    {
        free(cur_node1);
    }

    return cur_node;
}

//==========================================================================================================================================

int simplification(Tree* init_tree, Node* root)
{
    if(init_tree->error_code != SUCCESS)
    {   
        return init_tree->error_code;
    }

    if(root == nullptr)
    {
        init_tree->error_code = ERROR_BAD_SIMPLIFICATION;
        RETURN_DIFF_ERROR(ERROR_BAD_SIMPLIFICATION);
    }
    
    if(root->left_child != nullptr)
    {
        simplification(init_tree, root->left_child);
    }

    if(root->right_child != nullptr)
    {
        simplification(init_tree, root->right_child);
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
                    init_tree->error_code = ERROR_DEVISION_BY_ZERO;
                    RETURN_DIFF_ERROR(ERROR_DEVISION_BY_ZERO);
                }

                root->val.number = root->left_child->val.number / root->right_child->val.number;
            }

            else if(root->val.op_code == '^')
            {
                if(float_comparison(root->left_child->val.number, 0) == UNDER)
                {
                    init_tree->error_code = ERROR_NEG_NUMBER_DEGREE;
                    RETURN_DIFF_ERROR(ERROR_NEG_NUMBER_DEGREE);
                }

                root->val.number = pow(root->left_child->val.number, root->right_child->val.number);
            }

            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }

        else if(((root->left_child->type != NUM)  && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 0) == EQUAL)  && (root->val.op_code == '*')) ||
                ((root->right_child->type != NUM) && (root->left_child->type  == NUM) && (float_comparison(root->left_child->val.number, 0)  == EQUAL)  && (root->val.op_code == '*')))
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
                root->left_child->parent = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child = root->left_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->left_child;
                }

                root->parent     = nullptr;
                root->left_child = nullptr;

                childs_dtor(root);
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
                root->right_child->parent = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child  = root->right_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->right_child;
                }

                root->parent      = nullptr;
                root->right_child = nullptr;

                childs_dtor(root);
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
                root->left_child->parent = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child = root->left_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->right_child;
                }

                root->parent      = nullptr;
                root->right_child = nullptr;

                childs_dtor(root);
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
                root->left_child->parent = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child = root->left_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->left_child;
                }

                root->parent     = nullptr;
                root->left_child = nullptr;

                childs_dtor(root);
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
                root->right_child->parent = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child  = root->right_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->right_child;
                }

                root->parent      = nullptr;
                root->right_child = nullptr;

                childs_dtor(root);
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
                root->left_child->parent  = root->parent;

                if(root->parent->left_child == root)
                {
                    root->parent->left_child = root->left_child;
                }

                else if(root->parent->right_child == root)
                {
                    root->parent->right_child = root->left_child;
                }

                root->parent     = nullptr;
                root->left_child = nullptr;

                childs_dtor(root);
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
                ((root->left_child->type != NUM) && (root->right_child->type == NUM) && (float_comparison(root->right_child->val.number, 0) == EQUAL)  && (root->val.op_code == '^')))
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

        else if((root->left_child->type == NUM) && (float_comparison(root->left_child->val.number, 0) == EQUAL) && (root->val.op_code == '/'))
        {
            root->type = NUM;
            root->val.number = 0;
            childs_dtor(root->left_child);
            root->left_child = nullptr;
            childs_dtor(root->right_child);
            root->right_child = nullptr;
        }
    }

    return SUCCESS;
}
