#include "InputOutput.h"
#include "Common.h"
#include "QuadraticEquation.h"

//========================================================================================================================

void InputCoeff(double* a, double* b, double* c)
{
    assert(a != nullptr);
    assert(b != nullptr);
    assert(c != nullptr);

    printf("Hello. This program solves quadratic equations.\n"
           "Please enter 3 coefficients a, b and c of the quadratic equation ax^2 + bx + c = 0 separated by a space: ");

    while (scanf("%lf %lf %lf", a, b, c) != 3)  
    {
        ClearInputBuffer();
        
        printf("You did something wrong. You will be fired.\n"
               "Enter the coefficients of the quadratic equation one more time to prevent this: ");
    }
}

//========================================================================================================================

void OutputProcessing(const double* x1, const double* x2, const Roots nRoots)                   
{
    switch (nRoots)
    {
        case NoRoots:         printf("No solution.\n");                                  break;
        case InfinitiveRoots: printf("Infinitive solutions.\n");                         break; 
        case OneRoot:         printf("One solution x = %f.\n", *x1);                     break;
        case TwoRoots:        printf("Two solutions: x1 = %f and x2 = %f.\n", *x1, *x2); break;
        default:              assert(0 && "Undefined number of root. And I'm Groot.");   break;
    }
}