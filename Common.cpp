#include "Common.h"

//===========================================================================

static const double FloatConstant = 1E-6;

//===========================================================================

ComparisonResult FloatComparison(const double x1, const double x2)
{
    if (fabs(x1 - x2) <= FloatConstant)
        return EQUAL;

    else 
        return ((x1-x2) > FloatConstant) ? OVER : UNDER;
}

//===========================================================================

void ClearInputBuffer()
{
    while (getchar() != '\n' && getchar() != EOF)
        ;
}

//===========================================================================

int Swap(double* x1, double* x2)
{
    double swap = *x1;

    if (FloatComparison(*x1, *x2) == UNDER)
        return TwoRoots;
    else
    {
        *x1 = *x2;
        *x2 = swap;

        return TwoRoots;
    }
}
