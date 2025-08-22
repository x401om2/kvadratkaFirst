
#include <stdio.h>
#include <math.h>


void conclusion(double *x1, double *x2 , int *nRoots);
void solveSquare(double a, double b, double c , double *x1, double *x2 , int *nRoots);
void square(double a, double b, double c, double *x1, double *x2, int *nRoots);
void linear(double b, double c, double *x1, int *nRoots);
void enteringOdds(double *a, double *b, double *c);
void cleanBuffer();
void inputDouble(double *value, const char *name);


int main() {

    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;
    int nRoots = 0;

    enteringOdds(&a , &b , &c);
    solveSquare(a, b, c, &x1, &x2, &nRoots);
    conclusion(&x1, &x2, &nRoots);

    return 0;
}

void enteringOdds(double *a, double *b, double *c){

    printf("Уравнения вида ax^2 + bx + c = 0\n");

    inputDouble(a , "a");
    inputDouble(b , "b");
    inputDouble(c , "c");
}
// 0.1 + 0.2 != 0.3
//
// 0.30000000000000000004
void solveSquare(double a, double b, double c , double *x1, double *x2 , int *nRoots) {
    if (a == 0) {
        linear(b, c, x1 , nRoots);
    } else {
        square(a, b, c, x1, x2, nRoots);
    }
}

void conclusion(double *x1, double *x2 , int *nRoots) {

    if (*nRoots == 0) {
        printf("Решений нет");
    }else if (*nRoots == -1) {
        printf("Решений бесконечное количество");
    } else if (*nRoots == 1) {
        printf("Решение есть. Корень : %lf" , *x1);
    } else {
        printf("Решения есть\n");
        printf("Корень1 : %lf\n" , *x1);
        printf("Корень2 : %lf" , *x2);
    }
}

void cleanBuffer() {
    while (getchar() != '\n');
}

void linear(double b,double c, double *x1, int *nRoots) {
    if (b == 0) {
        if (c == 0) {
            *nRoots = -1;
        } else {
            *nRoots = 0;
        }
    } else {
        *x1 = -c / b;
        *nRoots = 1;
    }
}

void square(double a, double b, double c, double *x1, double *x2, int *nRoots) {

    double discriminant = b*b - (4*a*c);
    if (discriminant > 0) {
        *x1 = (-b + sqrt(discriminant)) / (2*a);
        *x2 = (-b - sqrt(discriminant)) / (2*a);
        *nRoots = 2;

    } else if (discriminant == 0) {
        *x1 = -b / (2*a);
        *nRoots = 1;
    } else {
        *nRoots = 0;
    }

}

void inputDouble(double *value, const char *name) { //
    printf("Введите коэффициент %s (действительное число) : ", name);
    while (scanf("%lf", value) != 1) {
        printf("Ошибка! Введите число: ");
        cleanBuffer();
    }
}
