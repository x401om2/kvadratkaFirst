#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include "equation.h"
#include "colors.h"
#include <ctype.h>    // для isdigit, isspace
#include <string.h>   // для strcspn - ищет первое вхождение любого символа из заданного набора в строке

void conclusion(const equationData *ed);
void enteringOdds(equationData *ed);
void inputDouble(double *value, const char *name);
void cleanBuffer();

#endif
