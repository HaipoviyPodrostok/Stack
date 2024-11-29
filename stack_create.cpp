#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack_create.h"

int stack_constructor(stack_t* stk, int capacity) {
    
    stk->data = (stack_elem_t*) calloc((size_t) capacity + 2, sizeof(stack_elem_t));
    
    if (stk->data == NULL) {
        return ERROR_STACK_NULL_POINTER;
    }
    
    stk->size = 1;
    stk->data[0] = 0xDEDBABA;
    stk->capacity = capacity + 1;
    stk->data[stk->capacity] = 0xDEDDEAD;
    
    return 0;
}

int stack_destructor(stack_t* stk) {
    
    if (stk->data == NULL) {
        return ERROR_STACK_NULL_POINTER;
    }
    
    free(stk->data);
    
    stk->size = -1;
    stk->capacity = -1;
    stk->data = NULL;
    
    return 0;
}

stack_elem_t* stack_capacity_check(stack_t* stk) {
                               
    stack_elem_t* stack_data = NULL;
    size_t data_size = 0;

    stack_data = stk->data;
    data_size = (size_t) (stk->capacity + 1) * sizeof(stack_elem_t);

    if (stk->size >= stk->capacity) {
        data_size += sizeof(stack_elem_t);
        stack_data = (stack_elem_t*) realloc(stk->data, (size_t) data_size);  
        stk->capacity ++;
        stack_data[stk->capacity] = stack_data[stk->capacity - 1];
        stack_data[stk->capacity - 1] = 0;
    }

    return stack_data;
}


