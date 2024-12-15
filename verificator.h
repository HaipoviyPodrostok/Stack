#ifndef VERIFICATOR_H
#define VERIFICATOR_H

#include "stack_structs.h"

enum ERRORS {
    ERROR_STACK_NULL_POINTER = 2,
    ERROR_DATA_NULL_POINTER = 3,
    ERROR_NEGATIVE_SIZE = 4,
    ERROR_NEGATIVE_CAPACITY = 5,
    ERROR_SIZE_OVERFLOW = 6,
    ERROR_STACK_CANARY_BEGINING = 7,
    ERROR_STACK_CANARY_END = 8,
};

int stack_check(const stack_t* stk);
void stack_dump(const stack_t* stk);
int verificator(const stack_t* stk);
void print_error(const stack_t* stk);

#endif //VERIFICATOR_H