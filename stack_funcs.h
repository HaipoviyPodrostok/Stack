#ifndef STACK_FUNCS
#define STACK_FUNCS

#include "stack_structs.h"

int stack_push(stack_t* stk, stack_elem_t value);
stack_elem_t stack_pop(stack_t* stk);

#endif //STACK_FUNCS