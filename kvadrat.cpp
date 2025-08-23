//константы сделал и NAN сделал

#include <stdio.h>
#include <math.h>
#include <float.h>

const double EPSILON = 0.00001;

const int TWO_ROOTS = 2;
const int ONE_ROOT = 1;
const int ZERO_ROOTS = 0;
const int INF_OF_ROOTS = -1;

// -0.000 сделал

struct coefficients {
    double a;
    double b;
    double c;
};

struct results {
    double x1;
    double x2;

    int nRoots;
};

void conclusion(double *x1, double *x2 , int *nRoots);
void solveSquare(double a, double b, double c , double *x1, double *x2 , int *nRoots);
void square(double a, double b, double c, double *x1, double *x2, int *nRoots);
void linear(double b, double c, double *x1, int *nRoots);
void enteringOdds(double *a, double *b, double *c);
void cleanBuffer();
void inputDouble(double *value, const char *name);
int doubleCompare(double a, double b);
void testSolveSquare();

int main() {
    // Struct for coeffs
    double a = NAN, b = NAN, c = NAN;
    // Struct for roots
    double x1 = NAN, x2 = NAN;
    int nRoots = 0;

    enteringOdds(&a , &b , &c);
    solveSquare(a, b, c, &x1, &x2, &nRoots);
    conclusion(&x1, &x2, &nRoots);
    testSolveSquare();

    return 0;
}

void enteringOdds(double *a, double *b, double *c){

    printf("Уравнения вида ax^2 + bx + c = 0\n");

    inputDouble(a , "a");
    inputDouble(b , "b");
    inputDouble(c , "c");
}

void solveSquare(double a, double b, double c , double *x1, double *x2 , int *nRoots) {
    if (doubleCompare(a, 0)) {
        linear(b, c, x1 , nRoots);
    } else {
        square(a, b, c, x1, x2, nRoots);
    }
}

void conclusion(double *x1, double *x2 , int *nRoots) {

    if (*nRoots == ZERO_ROOTS) {
        printf("Решений нет\n");
    }else if (*nRoots == INF_OF_ROOTS) {
        printf("Решений бесконечное количество\n");
    } else if (*nRoots == ONE_ROOT) {
        printf("Решение есть. Корень : %lf\n" , *x1);
    } else {
        printf("Решения есть\n");
        printf("Корень1 : %lf\n" , *x1);
        printf("Корень2 : %lf\n" , *x2);
    }
}

void cleanBuffer() {
    while (getchar() != '\n');
}

void linear(double b,double c, double *x1, int *nRoots) {
    if (doubleCompare(b, 0)) {
        if (doubleCompare(c, 0)) {
            *nRoots = INF_OF_ROOTS;
        } else {
            *nRoots = ZERO_ROOTS;
        }
    } else {
        *x1 = -c / b;
        if (fabs(*x1) < EPSILON) {
            *x1 = 0.0;
        }
        *nRoots = ONE_ROOT;
    }
}

void square(double a, double b, double c, double *x1, double *x2, int *nRoots) {

    double discriminant = b*b - (4*a*c);

    if (discriminant > 0) {
        *x1 = (-b + sqrt(discriminant)) / (2*a);
        *x2 = (-b - sqrt(discriminant)) / (2*a);
        if (fabs(*x1) < EPSILON) {
            *x1 = 0.0;
        }
        if (fabs(*x2) < EPSILON) {
            *x2 = 0.0;
        }
        *nRoots = TWO_ROOTS;

    } else if (doubleCompare(discriminant, 0)) {
        *x1 = -b / (2*a);
        if (fabs(*x1) < EPSILON) {
            *x1 = 0.0;
        }
        *nRoots = ONE_ROOT;
    } else {
        *nRoots = ZERO_ROOTS;
    }

}

void inputDouble(double *value, const char *name) {
    printf("Введите коэффициент %s (действительное число) : ", name);
    while (scanf("%lf", value) != 1) {
        printf("Ошибка! Введите число: ");
        cleanBuffer();
    }
}

int doubleCompare(double a, double b) {
    if (fabs(a) < EPSILON && fabs(b) < EPSILON) {//случай для сравнения
        return 1;
    }
    return fabs(a - b) < EPSILON;
}

void testSolveSquare() {
    double x1 = 0 , x2 = 0;
    int nRoots = 0;

    solveSquare(1, -5, 6, &x1, &x2, &nRoots);

    if (!(nRoots == TWO_ROOTS && (doubleCompare(x1, 3)) && (doubleCompare(x2, 2)))) {
        printf("Failed: solveSquare(1, -5, 6) -> 2, x1 = %lf, x2 = %lf (should be x1 = 2, x2 = 3\n)" , x1, x2);
    }else {
        printf("good");
    }

}

