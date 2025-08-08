#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "stack_funcs.h"

#define THRESHOLD_OF_LINEAR_CAPACITY_GROWTH 100
#define ADDED_CELLS 10

static stack_err_t stack_overflow_check(stack_t* stk);

stack_err_t stack_ctor(stack_t* const stk,     const char* stk_name,
                       const size_t elem_size, const size_t capacity) {
    
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;
    
    strncpy(stk->name, stk_name, DEFAULT_STR_LEN);
    stk->name[DEFAULT_STR_LEN - 1] = '\0';

    stk->size = 0;
    stk->elem_size = elem_size;
    stk->capacity = capacity + ALLOC_RESERVE;
    stk->cell_size = CELL_SIZE(elem_size);

    const size_t data_size = DATA_SIZE(stk->capacity);

    stk->raw_mem = calloc(1, data_size);  //first canary ptr
    if (!stk->raw_mem) return STACK_ERR_ALLOCATION_FAILED;

    stk->data = (void*) ((char*) stk->raw_mem + sizeof(CANARY_TYPE));
    
    *((CANARY_TYPE*) stk->raw_mem) = LEFT_CANARY;

    CANARY_TYPE* last_canary_ptr = (CANARY_TYPE*) stk_data_offset(stk, stk->capacity);
    *last_canary_ptr = RIGHT_CANARY;

    return STACK_ERR_SUCCESS;
}

void stack_dtor(stack_t* const stk) {
    free(stk->raw_mem);

    stk->size = 0;
    stk->capacity = 0;
    stk->elem_size = 0;
    stk->data = NULL;
    stk->raw_mem = NULL;

    return;
}

stack_err_t stack_push(stack_t* const stk, const void* const value) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;
    
    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(stk_peak, value, stk->elem_size);

    void* padding = (void*) ((char*) stk_peak + stk->elem_size);
    assert(stk->elem_size <= stk->cell_size);
    memset(padding, 0xCC, (stk->cell_size - stk->elem_size));

    stk->size++;

    return STACK_ERR_SUCCESS;
}

stack_err_t stack_pop(stack_t* const stk, void* const value) {
    if (!stk || !value) return STACK_ERR_NULL_PTR_ERROR;
    
    stk->size--;

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(value, stk_peak, stk->elem_size);

    memset(stk_peak, 0, stk->elem_size);

    return STACK_ERR_SUCCESS;
}

void* stk_data_offset(const stack_t* const stk, const size_t offset_size) {
    char* base = (char*) stk->data;
    return base + offset_size * stk->cell_size;
}

static stack_err_t stack_overflow_check(stack_t* stk) { //TODO канарейки + дата 
    assert(stk);

    stack_t* new_stk = NULL;
    size_t new_stk_size = 0;

    if (stk->capacity <= THRESHOLD_OF_LINEAR_CAPACITY_GROWTH) {
        if (stk->size >= stk->capacity) {
            new_stk_size = DATA_SIZE(stk->capacity + ADDED_CELLS);
        }
        else if ((stk->capacity - stk->size) >= 2 * ALLOC_RESERVE) {
            new_stk_size = DATA_SIZE(stk->capacity + ADDED_CELLS);   
        }
    } else {
        if (stk->size >= stk->capacity) {
            new_stk_size = DATA_SIZE(stk->capacity * 2);
        }

        else if ((stk->capacity / stk->size) >= 2) {
            new_stk_size = DATA_SIZE(stk->capacity / 2);
        } 
    }

    new_stk = (stack_t*) realloc(stk, new_stk_size);
    if (!new_stk) return STACK_ERR_ALLOCATION_FAILED;

    return STACK_ERR_SUCCESS;
}