#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

//=====================================================================================

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include "Common.h"
#include "QuadraticEquation.h"

//=====================================================================================
/**
 * @brief OutputProcessing - takes 2 pointers to quadratic equation solutions
 *        and value nRoots. processes the data obtained after solving the quadratic 
 *        equation and displays the number of roots, and then the roots themselves.
 * 
 * @param x1 Pointer to the first root of the quadratic equation.
 * @param x2 Pointer to the second root of the quadratic equation.
 * @param nRoots Сalls a function SolveQuadratic.
 */
void OutputProcessing(const double* x1, const double* x2, const Roots nRoots);

//=====================================================================================
/**
 * @brief InputCoeff - takes 3 pointer to quadratic coefficients. 
 *        It also checks for the correctness of the input.
 * 
 * @param a Pointer to coefficient at x^2.
 * @param b Pointer to coefficient at x^1.
 * @param c Pointer to coefficient at x^0.
 */
void InputCoeff(double* a, double* b, double* c);

//=====================================================================================

#endif // INPUT_OUTPUT_H
