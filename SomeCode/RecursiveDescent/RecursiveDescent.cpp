#include "RecursiveDescent.h"

//==============================================================================

const char*          s = NULL;
int                  p = 0;

char* vars_ptr_arr[10] = { 0 };

int some_val = 0;

//==============================================================================

int getGen(const char* str)
{    
    printf("STRING: %s\n\n", str);
    
    s = str;
    p = 0;

    printf("Function getG.   s[p] = '%c'. p = %d\n\n", s[p], p);

    int val = getExp();

    assert(s[p++] == '\0');

    return val;
}

//==============================================================================

int getExp()
{
    printf("Function getSum. s[p] = '%c'. p = %d\n\n", s[p], p);

    int val = getMul();

    while(s[p] == '+' || s[p] == '-')
    {
        printf("Function getSum. s[p] = '%c'. p = %d\n\n", s[p], p);

        int op = s[p++];

        int val2 = getMul();

        if(op == '+')
        {
            val += val2;
        }

        else
        {
            val -= val2;
        }
    }

    return val;
}

//==============================================================================

int getMul()
{
    printf("Function getMul. s[p] = '%c'. p = %d\n\n", s[p], p);

    int val = getDeg();

    while(s[p] == '*' || s[p] == '/')
    {
        printf("Function getMul. s[p] = '%c'. p = %d\n\n", s[p], p);

        int op = s[p++];

        int val2 = getDeg();

        if(op == '*')
        {
            val *= val2;
        }

        else
        {
            val /= val2;
        }
    }

    return val;
}

//==============================================================================

int getDeg()
{
    printf("Function getPow. s[p] = '%c'. p = %d\n\n", s[p], p);

    int val = getBrt();

    if(s[p] == '^')
    {
        p++;
        
        int val2 = getBrt();

        val = (int)pow(val, val2);
    }

    return val;
}

//==============================================================================

int getBrt()
{
    printf("Function getBct. s[p] = '%c'. p = %d\n\n", s[p], p);

    if(s[p] == '(')
    {
        p++;

        int val = getExp();

        assert(s[p++] == ')');

        return val;
    }

    else if(s[p] >= '0' && s[p] <= '9')
    {
        return getNum();
    }

    else
    {
        return getWord();
    }
}

//==============================================================================

int getWord()
{
    printf("Function getWrd. s[p] = '%c'. p = %d\n\n", s[p], p);

    char* var = getVar();

    int val = 0;

    if(s[p] == '(')
    {
        printf("Function getWrd. s[p] = '%c'. p = %d\n\n", s[p], p);

        p++;

        val = getExp();

        if(!strcasecmp(var, "sqrt"))
        {
            val = (int)sqrt(val);
        }

        else if(!strcasecmp(var, "sin"))
        {
            val = (int)sin(val);
        }

        else if(!strcasecmp(var, "cos"))
        {
            val = (int)cos(val);
        }

        else if(!strcasecmp(var, "tg"))
        {
            val = (int)tan(val);
        }

        else if(!strcasecmp(var, "ctg"))
        {
            val = (int)(1 / tan(val));
        }

        else if(!strcasecmp(var, "arcsin"))
        {
            val = (int)asin(val);
        }

        else if(!strcasecmp(var, "arccos"))
        {
            val = (int)acos(val);
        }

        else if(!strcasecmp(var, "arctg"))
        {
            val = (int)atan(val);
        }

        else if(!strcasecmp(var, "arcctg"))
        {
            val = (int)(M_PI / 2 - atan(val));
        }

        else if(!strcasecmp(var, "sh"))
        {
            val = (int)sinh(val);
        }

        else if(!strcasecmp(var, "ch"))
        {
            val = (int)cosh(val);
        }

        else if(!strcasecmp(var, "ln"))
        {
            val = (int)log(val);
        }

        else if(!strcasecmp(var, "exp"))
        {
            val = (int)exp(val);
        }

        free(var);

        printf("Function getWrd. s[p] = '%c'. p = %d\n\n", s[p], p);

        assert(s[p++] == ')');
    }

    else
    {
        char* var_ptr = (char*)calloc(MAX_WORD_LEN, sizeof(char));
        assert(var_ptr != nullptr);

        strcpy(var_ptr, var);

        addVar(var_ptr);
    }

    return val;
}

//==============================================================================

char* getVar()
{
    char* var = (char*)calloc(MAX_WORD_LEN, sizeof(char));

    for(int i = 0; (s[p] >= 'A' && s[p] <= 'Z') || (s[p] >= 'a' && s[p] <= 'z'); i++, p++)
    {
        printf("Function getVar. s[p] = '%c'. p = %d\n\n", s[p], p);
        var[i] = s[p];
    }

    return var;
}

//==============================================================================

int getNum()
{
    int val = 0;
    int calls_num = p;

    while('0' <= s[p] && s[p] <= '9')
    {
        printf("Function getNum. s[p] = '%c'. p = %d\n\n", s[p], p);

        val = val*10 + s[p] - '0';

        p++;
    }

    assert(p > calls_num);

    return val;
}

//==============================================================================

void addVar(char* var_ptr)
{
    static int cur_var = 0;

    vars_ptr_arr[cur_var] = var_ptr;

    cur_var++;

    some_val = cur_var;
}
