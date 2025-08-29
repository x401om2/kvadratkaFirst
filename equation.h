#ifndef EQUATION_H
#define EQUATION_H

#include <math.h>

const double EPSILON = 10e-15;

typedef enum {
    INF_OF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    ERROR_ROOTS = 3
} countOfRoots;

typedef struct {
    double a, b, c;
    double x1, x2;
    countOfRoots nRoots;
} equationData;

void solveSquare(equationData *ed);
void linear(equationData *ed);
void square(equationData *ed);
int doubleCompare(double a, double b);
double fixNegative(double value);

#endif
