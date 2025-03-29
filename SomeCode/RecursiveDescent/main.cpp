#include "RecursiveDescent.h"

//==============================================================================

int main()
{
    int val = getGen("2^(2+2)*(1+2)*sqrt(4)/exp(2хх)");

    printf("%d\n", val);
}


// G == general
// E == exp
// T == mul
// D == deg
// P == brt | exp | word
// W == var | exp
// V == chars (isalpha)
// N == num


// getG ::= E'\0'
// getE ::= T{['+' | '-']T}*
// getT ::= D{['*' | '/']D}*
// getD ::= P && if '^' P
// getP ::= '(' E ')' | N | W
// getW ::= V && if '(' E ')'
// getV ::= ['A' - 'z']+
// getN ::= ['0' - '9']+

