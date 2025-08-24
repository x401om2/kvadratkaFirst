//  enum , юнит тесты - написал,  файловый ввод вывод , написать функцию для отрицательного нуля - написал

#include <stdio.h>
#include <math.h>
#include <float.h>

const double EPSILON = 0.00001;

typedef enum {
    INF_OF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2
} countOfRoots;

//K&R Прата
typedef struct {
    double a;
    double b;
    double c;
} coefficients;

typedef struct{
    double x1;
    double x2;
    //enum change
    countOfRoots nRoots;
} results;

void conclusion(const results *res); //ф-ия вывода - элементы поступают в него и дальше не меняются
void solveSquare(const coefficients *coeffs, results *res);//функция подсчета , входные данные уже есть                                                          //и не изм, а вот результатов еще нет
void square(const coefficients *coeffs, results *res);
void linear(const coefficients *coeffs, results *res);
void enteringOdds(coefficients *coeffs); //не const тк мы вводим элементы - меняются
void cleanBuffer();
void inputDouble(double *value, const char *name);

int doubleCompare(double a, double b);
double fixNegative(double value); //ф-ия против -0

int oneTest(double a, double b , double c, double x1ref, double x2ref, countOfRoots nRootsref);
void runTests();

int main() {
    coefficients coeffs = {NAN , NAN , NAN};
    results res = {NAN , NAN , ZERO_ROOTS};

    runTests();

    enteringOdds(&coeffs);
    solveSquare(&coeffs , &res);
    conclusion(&res);

    return 0;
}

void enteringOdds(coefficients *coeffs){

    printf("Уравнения вида ax^2 + bx + c = 0\n");

    inputDouble(&coeffs -> a , "a"); // берем адрес значения а структуры , на которую указывает coeffs
    inputDouble(&coeffs -> b , "b"); // потому что это ф-ия ввода и там нужно изменить значение по адресу
    inputDouble(&coeffs -> c , "c"); // на то которое введет пользователь
}

void solveSquare(const coefficients *coeffs , results *res) {
    if (doubleCompare(coeffs -> a, 0)) {
        linear(coeffs, res);
    } else {
        square(coeffs , res);
    }
}

void conclusion(const results *res) {
    switch (res->nRoots) {
        case ZERO_ROOTS :
            printf("Нет решений\n");
            break;
        case ONE_ROOT:
            printf("Решение есть. Корень: %lf\n", res->x1);
            break;
        case TWO_ROOTS:
            printf("Решения есть\n");
            printf("Корень1: %lf\n", res->x1);
            printf("Корень2: %lf\n", res->x2);
            break;
        case INF_OF_ROOTS:
            printf("Решений бесконечное количество\n");
            break;
        default:
            printf("Количество корней неизвестно\n");
    }
}

void cleanBuffer() {
    while (getchar() != '\n');
}

void linear(const coefficients *coeffs, results *res) {
    double b = coeffs->b;
    double c = coeffs->c;

    if (doubleCompare(b, 0)) {
        if (doubleCompare(c, 0)) {
            res -> nRoots = INF_OF_ROOTS;
        } else {
            res -> nRoots = ZERO_ROOTS;
        }
    } else {
        res->x1 = fixNegative(-c / b);

        res->nRoots = ONE_ROOT;
    }
}

void square(const coefficients *coeffs, results *res) {
    double a = coeffs->a;
    double b = coeffs->b;
    double c = coeffs->c;

    double discriminant = b*b - (4*a*c);

    if (discriminant > 0) {
        res->x1 = fixNegative((-b + sqrt(discriminant)) / (2*a));
        res->x2 = fixNegative((-b - sqrt(discriminant)) / (2*a));
        res -> nRoots = TWO_ROOTS;
    } else if (doubleCompare(discriminant, 0)) {
        res->x1 = fixNegative(-b  / (2*a));
        res -> nRoots = ONE_ROOT;
    } else {
        res -> nRoots = ZERO_ROOTS;
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
    return fabs(a - b) < EPSILON;
}

int oneTest(double a, double b, double c, double x1ref, double x2ref, countOfRoots nRootsref) {
    coefficients coeffs = {a, b, c};
    results res = {NAN, NAN, ZERO_ROOTS};

    solveSquare(&coeffs, &res);

    if (res.nRoots != nRootsref) {
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получилось корней = %d, а в действительности = %d\n", a, b, c, res.nRoots, nRootsref);
        return 0;
    }
    if (res.nRoots >= 1 && !doubleCompare(res.x1, x1ref)) {
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получилось x1 = %lf, а должно быть = %lf\n", a, b, c, res.x1, x1ref);
        return 0;
    }
    if (res.nRoots == TWO_ROOTS && !doubleCompare(res.x2, x2ref)) {
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получилось x2 = %lf, а должно быть = %lf\n", a, b, c, res.x2, x2ref);
        return 0;
    }
    return 1;
}

void runTests() {
    int passed = 0;
                    //a   b  c  x1 x2   nRoots
    passed += oneTest(1, -3, 2, 2, 1, TWO_ROOTS);
    passed += oneTest(1, -2, 1, 1, 0, ONE_ROOT);
    passed += oneTest(1, 0, 1, 0, 0, ZERO_ROOTS);
    passed += oneTest(0, 2, -4, 2, 0, ONE_ROOT);
    passed += oneTest(0, 0, 0, 0, 0, INF_OF_ROOTS);
    passed += oneTest(0, 0, 5, 0, 0, ZERO_ROOTS);

    if (passed == 6) {
        printf("Все тесты выполнены\n");
    } else {
        printf("Есть ошибка\n");
        printf("%d\n", passed);
    }
    printf("\n");
}

double fixNegative(double value) { // убирает -0
    if (fabs(value) < EPSILON) {
        return 0.0;
    }
    return value;
}
