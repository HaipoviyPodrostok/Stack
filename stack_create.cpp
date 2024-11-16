#include <stdio.h>
#include <stdlib.h>
#include "stack_create.h"

int stack_constructor(stack* stk, int capacity) {
    
    stk->data = (stack_elem*) calloc((size_t) capacity + 1, sizeof(stack_elem));
    
    if (stk->data == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    stk->size = 0;
    stk->capacity = capacity;
    
    return 0;
}

int stack_destructor(stack* stk) {
    
    if (stk->data == NULL) {
        return ERROR_NULL_POINTER;
    }
    
    free(stk->data);
    
    stk->size = -1;
    stk->capacity = -1;
    stk->data = NULL;
    
    return 0;
}

stack_elem* stack_capacity_check(stack* stk) {
    stack_elem* stack_data = 0;
    int stack_size = 0;
    int stack_capacity = 0;
    size_t data_size = 0;

    stack_data = stk->data;
    stack_size = stk->size;
    stack_capacity = stk->capacity;                                 //что выгоднее с точки зрения скорости?
    data_size = (size_t) (stack_capacity + 1) * sizeof(stack_elem);

    if (stack_size >= stack_capacity) {
        stack_capacity ++;
        data_size += sizeof(stack_elem);
        stack_data = (stack_elem*) realloc(stack_data, (size_t) data_size);   //проверка адреса
    }

    stk->capacity = stack_capacity;

    return stack_data;
}
