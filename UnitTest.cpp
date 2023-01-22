#include "UnitTest.h"
#include "QuadraticEquation.h"
#include "Common.h"

//=============================================================================================================================

struct UnitTest
{
    double a_s;
    double b_s;
    double c_s;

    int RootNumber_s;
    double x1_s;
    double x2_s;
};

//=============================================================================================================================

void TestingSolutions()
{
    printf("\n");

    struct UnitTest QuadraticEq[] =
        {
            {0,  0,  0, 3,        NAN,        NAN},
            {2,  0,  0, 1,          0,        NAN},
            {3,  4,  5, 0,        NAN,        NAN},
            {0,  6, -5, 1,   0.833333,        NAN},
            {0, 14,  0, 1,          0,        NAN},
            {5,  0, -1, 2,  -0.447214,   0.447214},
            {7,  0,  8, 0,        NAN,        NAN},
            {16, 7, -8, 2,  -0.958919,   0.521419}};

    int size = sizeof(QuadraticEq) / sizeof(QuadraticEq[0]);

    for (int i = 0; i < size; i++)
    {
        double a_s       = QuadraticEq[i].a_s;
        double b_s       = QuadraticEq[i].b_s;
        double c_s       = QuadraticEq[i].c_s;
        
        int RootNumber_s = QuadraticEq[i].RootNumber_s;
        double x1_s      = QuadraticEq[i].x1_s;
        double x2_s      = QuadraticEq[i].x2_s;

        double x1 = NAN, x2 = NAN;

        int RootNumber = SolveQuadratic(a_s, b_s, c_s, &x1, &x2);

        if (RootNumber != RootNumber_s)
            printf("Test %d failed. The number of roots is %d. Expected %d.\n\n", i, RootNumber, RootNumber_s);

        else 
            {
                if (isnanl(x1) && isnanl(x1_s))
                {
                    if (isnanl(x2) && isnanl(x2_s))
                        printf("Test #%d passed.\n\n", i+1);

                    else
                    {
                        if (FloatComparison(x2, x2_s) == EQUAL)
                            printf("Test #%d passed.\n\n", i+1);

                        else
                            printf("Test #%d failed. The root x2 = %lg of the equation did not match.\n"
                            "Expected: x2 = %lg.\n\n", i+1, x2, x2_s);
                    }
                }

                else
                {
                    if (isnanl(x2) && isnanl(x2_s))
                        printf("Test #%d passed.\n\n", i+1);

                    else
                    {
                        if (FloatComparison(x1, x1_s) == EQUAL)
                        {
                            if (FloatComparison(x2, x2_s) == EQUAL)
                                printf("Test #%d passed.\n\n", i+1);

                            else 
                                printf("Test #%d failed. The root x2 = %lg of the equation did not match.\n"
                                "Expected: x2 = %lg.\n\n", i+1, x2, x2_s);
                        }

                        else 
                        {
                            if (FloatComparison(x2, x2_s) == EQUAL)
                                printf("Test #%d failed. The root x1 = %lg of the equation did not match.\n"
                                "Expected: x1 = %lg.\n\n", i+1, x1, x1_s);

                            else
                            printf("Test %d failed. The roots x1 = %lg and x2 = %lg of the equation did not match.\n"
                                "Expected x1 = %lg and x2 = %lg.\n\n", i, x1, x2, x1_s, x2_s);
                        }
                    }
                }
            }
    }
}
