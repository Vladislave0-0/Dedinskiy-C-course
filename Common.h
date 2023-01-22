#ifndef COMMON_H
#define COMMON_H

//=====================================================================================

#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>

//=====================================================================================
/**
 * @brief notes comparing variables with type float.
 */
enum ComparisonResult
{
    UNDER = -1,
    EQUAL =  0,
    OVER  =  1,
};

//=====================================================================================
/**
 * @brief Notes the number of roots found.
 */
enum Roots
{
    NoRoots         = 0,
    OneRoot         = 1,
    TwoRoots        = 2, 
    InfinitiveRoots = 3,
};

//=====================================================================================
/**
 * @brief FloatComparison - compares variables with type float.
 * 
 * @param x1 First root of the quadratic equation.
 * @param x2 Second root of the quadratic equation.
 * @return value of enam
 * @see enum ComparisonResult
 */
ComparisonResult FloatComparison(const double x1, const double x2);

//=====================================================================================
/**
 * @brief ClearInputBuffer - erase the input when the user entered something wrong.
 */
void ClearInputBuffer();

//=====================================================================================

/**
 * @brief Swap - performs the exchange of variable values.
 * 
 * @param x1 First (and smallest) root of the equation
 * @param x2 Second (and biggest) root of the equation
 */
int Swap(double* x1, double* x2);

//=====================================================================================

#endif // COMMON_H
