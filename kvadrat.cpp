
#include <stdio.h>
#include <math.h>

#define infinityOfSolutions -1;
#define noSolutions -2;


//TODO: linear
//TODO: codestyle
void linear(double b , double c);

void square(double a, double b , double c);

void enteringOdds(double *a, double *b, double *c);

int main() {
    double a = 0, b = 0, c = 0;
    double x1 = 0, x2 = 0;

    enteringOdds(&a , &b , &c);

    if (a == 0){

        printf("Уравнение является линейным\n");
        linear(b , c);

    } else {

        printf("Уравнение является квадратным\n");
        square(a , b , c);
    }

    return 0;
}

/*
main()
{
    a,b,c,x1,x2, nRoots;
    // Input();
    // Solve();
    // Output();
}

*/

void linear(double b , double c) {

    double x = 0;

    if (b == 0) {
        if (c == 0) {
            printf("Бесконечное множество решений");

        } else {
            printf("Решений нет");
        }
    } else {

        x = -b / c;
        printf("Решением является : %lf", x);
    }

}


void square(double a, double b, double c) {

    double x1 = 0;
    double x2 = 0;

    double discriminant = b*b - (4*a*c);

    if (discriminant > 0) {
        x1 = (-b + sqrt(discriminant)) / (2*a);
        x2 = (-b - sqrt(discriminant)) / (2*a);

        printf("Первый корень : x1 = %lf\n" , x1);
        printf("Второй корень : x2 = %lf\n" , x2);

    } else if (discriminant == 0) {
        x1 = -b / (2*a);
        printf("Решение : x = %lf\n" , x1);
    } else {
        printf("Решений нет");
    }

}

void enteringOdds(double *a, double *b, double *c){
    printf("Уравнения вида ax^2 + bx + c = 0\n");

    printf("Введите коэффициент а (действительное число) : ");
    scanf("%lf" , a);

    printf("Введите коэффициент b (действительное число) : ");
    scanf("%lf" , b);
    //TODO: int success_elements = ...
    printf("Введите коэффициент c (действительное число) : ");
    scanf("%lf" , c);
}




