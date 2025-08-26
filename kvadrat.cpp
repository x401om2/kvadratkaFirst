#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>

const double EPSILON = 0.000001;

typedef enum {
    INF_OF_ROOTS = -1,
    ZERO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    ERROR_ROOTS = 3
} countOfRoots; // это тип данных , конкретный enum-тип

typedef struct {
    double a, b, c;
    double x1, x2;
    countOfRoots nRoots;
} equationData;

void conclusion(const equationData *ed); //ф-ия вывода - элементы поступают в него и дальше не меняются
void solveSquare(equationData *ed);//функция подсчета , входные данные уже есть                                                          //и не изм, а вот результатов еще нет
void square(equationData *ed);
void linear(equationData *ed);
void enteringOdds(equationData *ed);

void inputDouble(double *value, const char *name);
int doubleCompare(double a, double b);
void cleanBuffer();
double fixNegative(double value); //ф-ия против -0

int oneTest(equationData test);
void runTests();
void runTestsFromFile();
//////
void poltoraIIIka(const char *name);
//////

int main() {
    //                  a    b    c    x1   x2   nRoots
    poltoraIIIka("MEOW PEKUS or DED or MENTOR or anybody else");
    equationData ed = {NAN, NAN, NAN, NAN, NAN, ERROR_ROOTS};//начальная инициализация

    // runTests(); //тесты из программы
    runTestsFromFile(); // Запускаем тесты из файла

    enteringOdds(&ed);
    solveSquare(&ed);
    conclusion(&ed);

    poltoraIIIka("COMMIT GITHUB!!!!");

    return 0;
}

void enteringOdds(equationData *ed){
    assert(ed != NULL); // не пустой ли указатель
    assert(ed->nRoots == ERROR_ROOTS); //рутс в верном начальном состоянии

    printf("Уравнения вида ax^2 + bx + c = 0\n");

    inputDouble(&ed->a , "a"); // берем адрес значения а структуры , на которую указывает ed
    inputDouble(&ed->b , "b"); // потому что это ф-ия ввода и там нужно изменить значение по адресу
    inputDouble(&ed->c , "c"); // на то которое введет пользователь

    assert(!isnan(ed->a)); // проверка произошедшего ввода
    assert(!isnan(ed->b)); // чтобы все числа ввели успешно
    assert(!isnan(ed->c));

    assert(!isinf(ed->a)); // загуглил проверки на переполнение аргументов
    assert(!isinf(ed->b)); // чтобы не было бесконечных значений
    assert(!isinf(ed->c));
}

void solveSquare(equationData *ed) {
    assert(ed != NULL); //указатель не NULL(обращ по нулевому указателю - сегфолт - прога падает)
    assert(!isnan(ed->a));// элемент не должен оказаться NAN - посчитать ничего не выйдет
    assert(!isnan(ed->b));
    assert(!isnan(ed->c));

    if (doubleCompare(ed->a, 0)) {
        linear(ed);
    } else {
        square(ed);
    }
}

void conclusion(const equationData *ed) {
    assert(ed != NULL);
    assert(ed->nRoots >= INF_OF_ROOTS && ed->nRoots <= ERROR_ROOTS); //колво корней

    switch (ed->nRoots) {
        case ZERO_ROOTS :
            printf("Нет решений\n");
            break;
        case ONE_ROOT:
            printf("Решение есть. Корень: %lf\n", ed->x1);
            break;
        case TWO_ROOTS:
            printf("Решения есть\n");
            printf("Корень1: %lf\n", ed->x1);
            printf("Корень2: %lf\n", ed->x2);
            break;
        case INF_OF_ROOTS:
            printf("Решений бесконечное количество\n");
            break;
        case ERROR_ROOTS:
            printf("Ошибочное количество корней\n");
            break;
        default:
            printf("Количество корней неизвестно\n");
    }
    printf(" \n");
}

void linear(equationData *ed) {
    assert(ed != NULL);
    assert(doubleCompare(ed->a, 0)); //проверка на а = 0
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
    //TODO: Error roots check
    assert(ed != NULL); //assert NULL
    assert(!doubleCompare(ed->a, 0)); //ассерт 0
    assert(!isnan(ed->a)); //NAN чек
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

int oneTest(equationData test) { //test - мы передаем тестируемые значения

    assert(!isnan(test.a));
    assert(!isnan(test.b));
    assert(!isnan(test.c));
    assert(test.nRoots >= INF_OF_ROOTS && test.nRoots <= ERROR_ROOTS);

    equationData ed = test; //делаем копию тестируемых значений в аргументе  и передаем эти данные в ed

    solveSquare(&ed); //проводим вычисления с этими данными-копиями

    if (ed.nRoots != test.nRoots) { //ed.(...) - новые значения , test.(...) - ЭТАЛОНЫ, с которыми мы сравниваем
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получилось корней = %d, а в действительности = %d\n", test.a, test.b, test.c, ed.nRoots, test.nRoots);
        return 0;
    }
    if (ed.nRoots >= 1 && !doubleCompare(ed.x1, test.x1)) {
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получился x1 = %lf, а должен быть = %lf\n", test.a, test.b, test.c, ed.x1, test.x1);
        return 0;
    }
    if (ed.nRoots == TWO_ROOTS && !doubleCompare(ed.x2, test.x2)) {
        printf("Ошибка: из solveSquare(%lf, %lf, %lf) получился x2 = %lf, а должен быть = %lf\n", test.a, test.b, test.c, ed.x2, test.x2);
        return 0;
    }
    return 1;
}

void runTests() {
    //взял с лекции деда
    int passed = 0;

    equationData tests[] = {
    //   a  b   c  x1 x2  nRoots

        {1, -3, 2, 2, 1, TWO_ROOTS},
        {1, -2, 1, 1, 0, ONE_ROOT},
        {1, 0, 1, 0, 0, ZERO_ROOTS},
        {0, 2, -4, 2, 0, ONE_ROOT},
        {0, 0, 0, 0, 0, INF_OF_ROOTS},
        {0, 0, 5, 0, 0, ZERO_ROOTS},
        {1, 9, -10, 1, -10, TWO_ROOTS}
    };

    int countOfTests = sizeof(tests) / sizeof(tests[0]);

    assert(countOfTests > 0); // чтобы был хотя бы 1 тест

    for (int i = 0; i < countOfTests; i++) {
        assert(!isnan(tests[i].a));
        assert(!isnan(tests[i].b));
        assert(!isnan(tests[i].c));
        assert(tests[i].nRoots >= INF_OF_ROOTS && tests[i].nRoots <= ERROR_ROOTS);

        passed += oneTest(tests[i]);
    }
    if (passed == countOfTests) {
        printf("Все тесты выполнены\n");
    } else {
        printf("Есть ошибка\n");
        printf("%d\n", passed);
    }
    printf("\n");
}

double fixNegative(double value) { // убирает -0
    assert(!isnan(value));

    if (fabs(value) < EPSILON) {
        return 0.0;
    }
    return value;
}

void inputDouble(double *value, const char *name) {
    assert(value != NULL);
    assert(name != NULL);

    printf("Введите коэффициент %s (действительное число) : ", name);
    while (scanf("%lf", value) != 1) {
        printf("Ошибка! Введите число: ");
        cleanBuffer();
    }
    assert(!isnan(*value));
}

int doubleCompare(double a, double b) {
    assert(!isnan(a));
    assert(!isnan(b));

    return fabs(a - b) < EPSILON;
}

void cleanBuffer() {
    while (getchar() != '\n');
}

void runTestsFromFile() {
    FILE *file = fopen("tests.txt", "r");
    if (file == NULL) {
        printf("Не удалось открыть tests.txt\n"); //проверка на открытие - не указатель на пустое
        return;
    }

    int beforeNRoots = 0;
    int passed = 0;
    int totalTests = 0;

    while (!feof(file)) {
        equationData test; //интегрируем сюда тестовую структуру
        int countData = fscanf(file, "%lf %lf %lf %lf %lf %d",
                              &test.a, &test.b, &test.c,
                              &test.x1, &test.x2, &beforeNRoots); //считываем в нее элементы из файла
        test.nRoots = (countOfRoots)beforeNRoots;
        if (countData != 6) {
            break; // если взяли не 6 элементов - то выход
        }
        totalTests++;
        passed += oneTest(test);
    }
    fclose(file);
    printf("\nРезультаты: %d из %d тестов пройдено\n", passed, totalTests);
}




void poltoraIIIka(const char *name) {
    printf(" ");
    printf(" \n");
    printf("       ....／＞　 フ.....\n　　　　　| 　_　 _|\n　 　　　／`ミ _* 彡 -- %s!!\n　　 　 /　　　 　 |\n　　　 /　 ヽ　　 ﾉ\n　／￣|　　 |　|　|\n　| (￣ヽ＿_ヽ_)_)\n　＼二つ\n" ,name);
    printf(" \n");
    printf(" ");
}
