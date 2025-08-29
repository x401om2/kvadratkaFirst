#include <stdio.h>
#include <math.h>
#include <float.h>
#include <assert.h>
#include "equation.h"
#include "io_functions.h"
#include "tests.h"
#include "cat_art.h"

int main() {
    poltoraIIIka("MEOW PEKUS or DED or MENTOR or anybody else");

    equationData ed = {NAN, NAN, NAN, NAN, NAN, ERROR_ROOTS};

    runTests();
    //runTestsFromFile();

    enteringOdds(&ed);
    solveSquare(&ed);
    conclusion(&ed);

    poltoraIIIka("COMMIT GITHUB!!!!");

    return 0;
}
