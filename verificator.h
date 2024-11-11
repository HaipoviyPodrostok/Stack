#include "stack_structs.h"

enum ERRORS {
    ERROR_NULL_POINTER = 2,
    ERROR_NEGATIVE_SIZE = 3,
    ERROR_NEGATIVE_CAPACITY = 4,
    ERROR_SIZE_OVERFLOW = 5,
};

int stack_check(stack* stk);
void stack_dump(stack* stk);
int verificator(stack* stk);
void print_error(stack* stk);
