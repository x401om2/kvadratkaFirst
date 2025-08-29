#include "tests.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>



int oneTest(equationData test) {
    assert(!isnan(test.a));
    assert(!isnan(test.b));
    assert(!isnan(test.c));
    assert(test.nRoots >= INF_OF_ROOTS && test.nRoots <= ERROR_ROOTS);

    equationData ed = test;
    solveSquare(&ed);

    if (ed.nRoots != test.nRoots) {
        printf(RED "Ошибка: из solveSquare(%lf, %lf, %lf) получилось корней = %d, а в действительности = %d\n" RESET,
               test.a, test.b, test.c,
               ed.nRoots, test.nRoots);
        return 0;
    }
    if (ed.nRoots >= 1 && !doubleCompare(ed.x1, test.x1)) {
        printf(RED "Ошибка: из solveSquare(%lf, %lf, %lf) получился x1 = %lf, а должен быть = %lf\n" RESET,
               test.a, test.b, test.c,
               ed.x1, test.x1);
        return 0;
    }
    if (ed.nRoots == TWO_ROOTS && !doubleCompare(ed.x2, test.x2)) {
        printf(RED "Ошибка: из solveSquare(%lf, %lf, %lf) получился x2 = %lf, а должен быть = %lf\n" RESET,
               test.a, test.b, test.c,
               ed.x2, test.x2);
        return 0;
    }
    return 1;
}

void runTests() {
    int passed = 0;

    equationData tests[] = {
        {1, -3, 2, 2, 1, TWO_ROOTS},
        {1, -2, 1, 1, 0, ONE_ROOT},
        {1, 0, 1, 0, 0, ZERO_ROOTS},
        {0, 2, -4, 2, 0, ONE_ROOT},
        {0, 0, 0, 0, 0, INF_OF_ROOTS},
        {0, 0, 5, 0, 0, ZERO_ROOTS},
        {1, 9, -10, 1, -10, TWO_ROOTS}
    };

    int countOfTests = sizeof(tests) / sizeof(tests[0]);
    assert(countOfTests > 0);

    for (int i = 0; i < countOfTests; i++) {
        assert(!isnan(tests[i].a));
        assert(!isnan(tests[i].b));
        assert(!isnan(tests[i].c));
        assert(tests[i].nRoots >= INF_OF_ROOTS && tests[i].nRoots <= ERROR_ROOTS);
        passed += oneTest(tests[i]);
    }

    if (passed == countOfTests) {
        printf(" \n");
        printf(GREEN "ВCE ТЕСТЫ ВЫПОЛНЕНЫ\n" RESET);
    } else {
        printf(RED "Есть ошибка\n" RESET);
        printf("%d\n", passed);
    }
    printf("\n");
}

void runTestsFromFile() {
    FILE *file = fopen("tests.txt", "r");
    if (file == NULL) {
        printf("Не удалось открыть tests.txt\n");
        return;
    }

    int beforeNRoots = 0;
    int passed = 0;
    int totalTests = 0;

    while (!feof(file)) { //пока файл не заканчивается
        equationData test;
        int countData = fscanf(file, "%lf %lf %lf %lf %lf %d",
                              &test.a, &test.b, &test.c,
                              &test.x1, &test.x2, &beforeNRoots); //возвращ колво введ элементов
        test.nRoots = (countOfRoots)beforeNRoots;
        if (countData != 6) {
            break;
        }
        totalTests++;
        passed += oneTest(test);
    }
    fclose(file);
    printf("\nРезультаты: %d из %d тестов пройдено\n", passed, totalTests);
}
