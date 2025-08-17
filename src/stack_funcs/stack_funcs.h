#ifndef STACK_FUNCS_H
#define STACK_FUNCS_H

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <stddef.h>

#include "stack_err_handle.h"
#include "stack_structs.h"
#include "logger.h"
#include "verificator.h"

stack_err_t stack_ctor(stack_t* const stk,     const char* stk_name,
                       const size_t elem_size, const size_t capacity);
void stack_dtor(stack_t* const stk);
stack_err_t stack_push(stack_t* const stk, const void* const value);
stack_err_t stack_pop(stack_t* const stk, void* const value);
void* stk_data_offset(const stack_t* const stk, const size_t offset_size);
size_t align_up(const size_t size, const size_t align);
uint64_t calc_struct_hash(stack_t* const stk);
uint64_t calc_data_hash(stack_t* const stk);
uint64_t stack_hash(const void *data, const size_t len, const uint64_t seed);
void stack_rehash(stack_t* const stk);

#endif //STACK_FUNCS_H