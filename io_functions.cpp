#include "io_functions.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <ctype.h>    // для isdigit, isspace
#include <string.h>   // для strcspn - ищет первое вхождение любого символа из заданного набора в строке

void conclusion(const equationData *ed) {
    assert(ed != NULL);
    assert(ed->nRoots >= INF_OF_ROOTS && ed->nRoots <= ERROR_ROOTS);

    switch (ed->nRoots) {
        case ZERO_ROOTS :
            printf(" \n");
            printf("НЕТ РЕШЕНИЙ\n");
            break;
        case ONE_ROOT:
            printf(" \n");
            printf("ОТВЕТ: РЕШЕНИЕ ЕСТЬ. КОРЕНЬ: %lf\n", ed->x1);
            break;
        case TWO_ROOTS:
            printf(" \n");
            printf("ОТВЕТ: РЕШЕНИЯ ЕСТЬ\n");
            printf("Корень1: %lf\n", ed->x1);
            printf("Корень2: %lf\n", ed->x2);
            break;
        case INF_OF_ROOTS:
            printf(" \n");
            printf("ОТВЕТ: РЕШЕНИЙ БЕСКОНЕЧНОЕ КОЛИЧЕСТВО\n");
            break;
        case ERROR_ROOTS:
            printf("ОШИБОЧНОЕ КОЛИЧЕСТВО КОРНЕЙ\n");
            break;
        default:
            printf("КОЛИЧЕСТВО КОРНЕЙ НЕИЗВЕСТНО\n");
    }
    printf(" \n");
}

void enteringOdds(equationData *ed) {
    assert(ed != NULL);
    assert(ed->nRoots == ERROR_ROOTS);

    printf("Вы можете решить уравнение вида ax^2 + bx + c = 0\n");
    printf("Для этого вам необходимо ввести коэффициенты а b c по очереди\n");

    inputDouble(&ed->a , "a");
    inputDouble(&ed->b , "b");
    inputDouble(&ed->c , "c");

    assert(!isnan(ed->a));
    assert(!isnan(ed->b));
    assert(!isnan(ed->c));
    assert(!isinf(ed->a));
    assert(!isinf(ed->b));
    assert(!isinf(ed->c));
}

void inputDouble(double *value, const char *name) {
    assert(value != NULL);
    assert(name != NULL);

    char buffer[100];

    while (1) { // цикл пока не получим число для вычисления
        printf(" \n");
        printf("ВВЕДИТЕ КОЭФФИЦИЕНТ %s: ", name);

        if (fgets(buffer, sizeof(buffer), stdin) == NULL) { //читаем строку до появления первого симв нов строки
            printf(" \n");
            printf("ОШИБКА ЧТЕНИЯ. ПОПРОБУЙТЕ СНОВА.\n");
            cleanBuffer();
            continue; //переход к след итерации
        }

        buffer[strcspn(buffer, "\n")] = '\0'; //убираем перевод на нов строку(конспект функции есть)

        if (buffer[0] == '\0') { //если остался '\0' после удал "\n" то пустой ввод
            printf(" \n");
            printf("ВАШ ВВОД НИЧЕГО НЕ СОДЕРЖИТ. ВВЕДИТЕ ЧИСЛО.\n");
            continue;
        }

        int valid = 1; //состояние правильное/неправильное (нач - правильное)
        int digits = 0; //цифры
        int dots = 0; //точки

        for (int i = 0; buffer[i] != '\0'; i++) { //проход по символам
            if (isdigit(buffer[i])) {
                digits++;
            } else if (buffer[i] == '.') {
                dots++;
                if (dots > 1) {
                    valid = 0; //это не число так как больше одной точки
                    break;
                }
            } else if (buffer[i] == '+' || buffer[i] == '-') {
                if (i != 0) {
                    valid = 0; //если знак стоит не в начале числа то неверный ввод
                    break;
                }
            } else if (!isspace(buffer[i])) { //если не пробельный символ (запятые, буквы)
                valid = 0;
                break;
            }
        }
        if (!valid || digits == 0) { //если неправ ввод или нет цифр
            printf(" \n");
            printf("ОШИБКА! ИСПОЛЬЗУЙТЕ ТОЛЬКО: цифры 0-9, знаки + или -, точку - .\n");
            continue;
        }
        // Преобразуем в число
        char *endptr; //указат на первый символ неправильный , endptr + 1 указатель на след за ним символ
        double result = strtod(buffer, &endptr);  //123.45a result = 123.45

        // Проверяем остаток строки
        while (*endptr != '\0') { //пока символ не явл симв оконч строки
            if (!isspace(*endptr)) { //если не пробельный символ, символ для записи числа
                printf(" \n");
                printf("ОШИБКА! ЛИШНИЕ СИМВОЛЫ В КОНЦЕ.\n");
                valid = 0;
                break;
            }
            endptr++; //переход к след символу
        }
        if (!valid) continue; //если не число то продолжаем цикл ввода значений(просим ввести заново)
        *value = result; //записываем результат ввода по указателю
        break; // Успешный ввод
    }
}

void cleanBuffer() {
    while (getchar() != '\n');
}
