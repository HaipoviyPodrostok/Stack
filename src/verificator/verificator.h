#ifndef VERIFICATOR_H
#define VERIFICATOR_H

#include <stdio.h>
#include <stdint.h>

#include "stack_structs.h"
#include "stack_err_handle.h"

stack_err_t stack_verificator(stack_t* const stk);
stack_err_t stack_dump(stack_t* const stk);
stack_err_t validate(stack_t* const stk);

#endif //VERIFICATOR_H