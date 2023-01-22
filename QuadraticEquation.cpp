#include "QuadraticEquation.h"

//========================================================================================================================

int SolveQuadratic(const double a, const double b, const double c, double* x1, double* x2)           
{
    if (FloatComparison(a, 0) == EQUAL)
        return SolveLinear(b, c, x1);

    else
    {
        double Discriminant = b*b - 4*a*c;
        double DiscriminantSqrt = sqrt(Discriminant);
        

        if (FloatComparison(Discriminant, 0) == UNDER)
            return NoRoots;

        else if (FloatComparison(Discriminant, 0) == EQUAL) 
        {
            *x1 = -b / (2*a);

            if (FloatComparison(b, 0) == EQUAL)
                *x1 = 0;

            return OneRoot;
        }

        else
        {
            if (FloatComparison(c, 0) == EQUAL)
            {
                *x1 = 0;
                *x2 = -b / a;

                if (FloatComparison(b, 0) == EQUAL)
                {
                    *x1 = 0;
                    return OneRoot;
                }

                if (FloatComparison(*x1, *x2) == EQUAL)
                    return OneRoot;

                return Swap(x1, x2);
            }

            else
            {
                *x1 = (-b + DiscriminantSqrt) / (2*a);
                *x2 = (-b - DiscriminantSqrt) / (2*a);
                
                if (FloatComparison(*x1, *x2) == EQUAL)
                    return OneRoot;

                return Swap(x1, x2);
            }
        }
    }

    return 0;
}

//========================================================================================================================

int SolveLinear(const double b, const double c, double* x1)                                               
{
    if (FloatComparison(b, 0) == EQUAL)
        return (FloatComparison(c, 0) == EQUAL) ? InfinitiveRoots : NoRoots;
    else 
    {
        *x1 = -c / b;
        if (FloatComparison(c, 0) == EQUAL)
            *x1 = 0;

        return OneRoot;
    }
}
