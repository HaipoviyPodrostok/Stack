#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include "../../utils/error_handling.h"
#include "../stack_structs.h"

stack_err_t stack_ctor(stack_t* const stk, const size_t elem_size, const size_t capacity);

#endif //STACK_FUNCS_H