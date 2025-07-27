#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "stack_funcs.h"

static size_t calc_data_size(const size_t elem_size, const size_t capacity);
static void* stk_data_offset(const stack_t* const stk, const size_t offset_size);

stack_err_t stack_ctor(stack_t* const stk, const size_t elem_size, const size_t capacity) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;

    const size_t data_size = calc_data_size(elem_size, capacity);

    log_open("log/log_file.txt");

    stk->raw_mem = calloc(data_size, elem_size);  //with canaries
    if (!stk->raw_mem) return STACK_ERR_ALLOCATION_FAILED;
    LOG(DEBUG, "mem calloced");

    *((CANNARY_TYPE*) stk->raw_mem) = FIRST_CANNARY;

    stk->size = 0;
    stk->capacity = capacity + ALLOC_RESERVE;
    stk->data = (void*) ((char*) stk->raw_mem + sizeof(CANNARY_TYPE));

    CANNARY_TYPE* last_cannary_ptr = (CANNARY_TYPE*) stk_data_offset(stk, stk->capacity);
    *last_cannary_ptr = LAST_CANNARY;

    log_close();

    return STACK_ERR_SUCCES;
}

stack_err_t stack_dtor(stack_t* const stk) {
    assert(stk);

    free(stk->raw_mem);

    stk->size = 0;
    stk->capacity = 0;
    stk->elem_size = 0;
    stk->data = NULL;
    stk->raw_mem = NULL;

    return STACK_ERR_SUCCES;
}

static size_t calc_data_size(const size_t elem_size, const size_t capacity) {
    size_t data_size = elem_size * (capacity + ALLOC_RESERVE) + (sizeof(CANNARY_TYPE) * 2);
    return data_size; 
}

stack_err_t stack_push(stack_t* const stk, const void* const value) {
    assert(stk);

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(stk_peak, value, stk->elem_size);
    
    stk->size++;

    return STACK_ERR_SUCCES;
}

stack_err_t stack_pop(stack_t* const stk, void* const value) {
    assert(stk);
    
    stk->size--;

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(value, stk_peak, stk->elem_size);

    memset(stk_peak, 0, stk->elem_size);

    return STACK_ERR_SUCCES;
}

static void* stk_data_offset(const stack_t* const stk, const size_t offset_size) {
    char* base = (char*) stk->data;
    return base + offset_size * stk->elem_size;
}