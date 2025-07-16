#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "error_handling.h"

#define CASE_ENUM_TO_STRING(error) case error: return #error

const char* stack_error_str(stack_err_t error) {
    switch(error) {
        CASE_ENUM_TO_STRING(STACK_ERR_SUCCES);

        default:
            return "STACK_ERR_UNKNOWN_ERROR";
        return "STACK_ERR_UNKNOWN_ERROR";
    }
}

#undef CASE_ENUM_TO_STRING

bool isEqual (double x, double y) {
    const double EPSILON = 1e-6;
    return fabs (x - y) < EPSILON;
}
