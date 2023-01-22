#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

//==============================================================================================

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "Common.h"
#include "InputOutput.h"

//==============================================================================================
/**
 * @brief SolveQuadratic - takes 3 quadratic coefficients and 
 *        2 pointers to quadratic equation solutions.
 * 
 * @param a Coefficient at x^2.
 * @param b Coefficient at x^1.
 * @param c Coefficient at x^0.
 * @param x1 Pointer to the first root of the quadratic equation.
 * @param x2 Pointer to the second root of the quadratic equation.
 * 
 * @return one of the values of enum. 
 * @see enum Roots.
 */
int SolveQuadratic(const double a, const double b, const double c, double* x1, double* x2);

//==============================================================================================
/**
 * @brief SolveLinear - a special case of a function SolveQuadratic if a == 0.
 *        Takes 2 quadratic coefficients b and c and pointer to the root of the
 *        quadratic equation.
 * 
 * @param b Coefficient at x^1.
 * @param c Coefficient at x^0.
 * @param x1 Pointer to the root of the quadratic equation.
 * 
 * @return values of enum. 
 * @see enum Roots.
 */
int SolveLinear(const double b, const double c, double* x1);

//==============================================================================================

#endif // QUADRATIC_EQUATION_H
