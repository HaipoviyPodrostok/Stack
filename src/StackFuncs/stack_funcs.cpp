#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "stack_funcs.h"

static size_t calc_data_size(const size_t elem_size, const size_t capacity);

stack_err_t stack_ctor(stack_t* const stk, const size_t elem_size, const size_t capacity) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;

    const size_t data_size = calc_data_size(elem_size, capacity);

    stk->raw_mem = calloc(data_size, elem_size);  //with canaries
    if (!stk->raw_mem) return STACK_ERR_ALLOCATION_FAILED;

    *((CANNARY_TYPE*) stk->raw_mem) = FIRST_CANNARY;

    stk->size = 0;
    stk->capacity = capacity + ALLOC_RESERVE;
    stk->data = (void*) ((char*) stk->raw_mem + sizeof(CANNARY_TYPE));

    CANNARY_TYPE* last_cannary_ptr = (CANNARY_TYPE*) ((char*) stk->data + (elem_size * capacity));
    *last_cannary_ptr= LAST_CANNARY;

    return STACK_ERR_SUCCES;
}

stack_err_t stack_dtor(stack_t* const stk) {

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

void stack_capacity_check(stack_t* stk) {
                               
    size_t data_size = 0;

    data_size = (size_t) (stk->capacity) * sizeof(stack_elem_t) + 2 * sizeof(unsigned long long);  

    if (stk->size >= stk->capacity) {
        
        data_size += 10 * sizeof(stack_elem_t);
        stk->data = (stack_elem_t*) realloc(stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t), data_size);  
        stk->data = stk->data + sizeof(unsigned long long) / sizeof(stack_elem_t);
        stk->capacity += 10;
        
        stk->data[stk->capacity] = stk->data[stk->capacity - 10]; // 
        stk->data[stk->capacity - 10] = 0;
    }

    else if (stk->capacity - stk->size == 20) {
        
        stk->data[stk->capacity - 10] = stk->data[stk->capacity];
        stk->data[stk->capacity] = 0;
        
        data_size -= 10 * sizeof(stack_elem_t);
        stk->data = (stack_elem_t*) realloc(stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t), data_size);
        stk->data = stk->data + sizeof(unsigned long long) / sizeof(stack_elem_t);
        stk->capacity -= 10;      
    }
    
}
