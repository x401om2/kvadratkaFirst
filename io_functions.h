#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include "equation.h"

void conclusion(const equationData *ed);
void enteringOdds(equationData *ed);
void inputDouble(double *value, const char *name);
void cleanBuffer();

#endif
