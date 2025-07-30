#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "stack_funcs.h"

static void* stk_data_offset(const stack_t* const stk, const size_t offset_size);

stack_err_t stack_ctor(stack_t* const stk, const size_t elem_size, const size_t capacity) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;
    
    stk->size = 0;
    stk->elem_size = elem_size;
    stk->capacity = capacity + ALLOC_RESERVE;

    const size_t data_size = (stk->capacity) * CELL_SIZE
                           + sizeof(FIRST_CANNARY)
                           + sizeof(LAST_CANNARY);

    stk->raw_mem = calloc(1, data_size);  //first cannary ptr
    if (!stk->raw_mem) return STACK_ERR_ALLOCATION_FAILED;

    stk->data = (void*) ((char*) stk->raw_mem + sizeof(CANNARY_TYPE));
    
    *((CANNARY_TYPE*) stk->raw_mem) = FIRST_CANNARY;

    CANNARY_TYPE* last_cannary_ptr = (CANNARY_TYPE*) stk_data_offset(stk, stk->capacity);
    *last_cannary_ptr = LAST_CANNARY;

    return STACK_ERR_SUCCES;
}

void stack_dtor(stack_t* const stk) {
    free(stk->raw_mem);

    stk->size = 0;
    stk->capacity = 0;
    stk->elem_size = 0;
    stk->data = NULL;
    stk->raw_mem = NULL;
}

stack_err_t stack_push(stack_t* const stk, const void* const value) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(stk_peak, value, stk->elem_size);
    
    stk->size++;

    return STACK_ERR_SUCCES;
}

stack_err_t stack_pop(stack_t* const stk, void* const value) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;
    
    stk->size--;

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(value, stk_peak, stk->elem_size);

    memset(stk_peak, 0, stk->elem_size);

    return STACK_ERR_SUCCES;
}

static void* stk_data_offset(const stack_t* const stk, const size_t offset_size) {
    char* base = (char*) stk->data;
    return base + offset_size * CELL_SIZE;
}