#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include "stack_err_handle.h"
#include "stack_structs.h"
#include "logger.h"

stack_err_t stack_ctor(stack_t* const stk, const size_t elem_size, const size_t capacity);
void stack_dtor(stack_t* const stk);
stack_err_t stack_push(stack_t* const stk, const void* const value);
stack_err_t stack_pop(stack_t* const stk, void* const value);

#endif //STACK_FUNCS_H