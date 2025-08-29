#include "equation.h"
#include <assert.h>
#include <math.h>

void solveSquare(equationData *ed) {
    assert(ed != NULL);
    assert(!isnan(ed->a));
    assert(!isnan(ed->b));
    assert(!isnan(ed->c));

    if (doubleCompare(ed->a, 0)) {
        linear(ed);
    } else {
        square(ed);
    }
}

void linear(equationData *ed) {
    assert(ed != NULL);
    assert(doubleCompare(ed->a, 0));
    assert(!isnan(ed->b));
    assert(!isnan(ed->c));

    double b = ed->b;
    double c = ed->c;

    if (doubleCompare(b, 0)) {
        if (doubleCompare(c, 0)) {
            ed->nRoots = INF_OF_ROOTS;
        } else {
            ed->nRoots = ZERO_ROOTS;
        }
    } else {
        assert(!doubleCompare(b, 0));
        ed->x1 = fixNegative(-c / b);
        ed->nRoots = ONE_ROOT;
    }
}

void square(equationData *ed) {
    assert(ed != NULL);
    assert(!doubleCompare(ed->a, 0));
    assert(!isnan(ed->a));
    assert(!isnan(ed->b));
    assert(!isnan(ed->c));

    double a = ed->a;
    double b = ed->b;
    double c = ed->c;

    double discriminant = b*b - (4*a*c);

    if (discriminant > 0) {
        assert(!doubleCompare(a, 0));
        ed->x1 = fixNegative((-b + sqrt(discriminant)) / (2*a));
        ed->x2 = fixNegative((-b - sqrt(discriminant)) / (2*a));
        ed->nRoots = TWO_ROOTS;
    }
    else if (doubleCompare(discriminant, 0)) {
        assert(!doubleCompare(a, 0));
        ed->x1 = fixNegative(-b  / (2*a));
        ed->nRoots = ONE_ROOT;
    }
    else {
        ed->nRoots = ZERO_ROOTS;
    }
}

int doubleCompare(double a, double b) {
    return fabs(a - b) < EPSILON;
}

double fixNegative(double value) {
    assert(!isnan(value));
    if (fabs(value) < EPSILON) {
        return 0.0;
    }
    return value;
}
