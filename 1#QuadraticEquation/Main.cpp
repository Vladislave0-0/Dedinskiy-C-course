// #define NDEBUG
//====================================================================

#include "QuadraticEquation.h"
#include "UnitTest.h"
#include "InputOutput.h"

//====================================================================

int main() 
{

#ifndef NDEBUG
    TestingSolutions();
#else
    double a  = NAN,
           b  = NAN,
           c  = NAN, 
           x1 = NAN, 
           x2 = NAN;
    
    InputCoeff(&a, &b, &c);

    Roots nRoots = (Roots)SolveQuadratic(a, b, c, &x1, &x2);

    OutputProcessing(&x1, &x2, nRoots);
    
#endif

    return 0;
}
