#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "stack_create.h"

int stack_ctor(stack_t* stk, int capacity) {
    
    stk->data = (stack_elem_t*) calloc((size_t) capacity + 10 + 2 * (sizeof(unsigned long long) / sizeof(stack_elem_t)), sizeof(stack_elem_t));   
    
    *(stk->data) = 0xDEDBABA;
    
    stk->size = 0;
    stk->capacity = capacity + 10;
    stk->data = stk->data + sizeof(unsigned long long) / sizeof(stack_elem_t);      

    stk->data[stk->capacity] = 0xDEDDEAD;
    
    return 0;
}

int stack_dtor(stack_t* stk) {
    
    free(stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t));
    
    stk->size = -1;
    stk->capacity = -1;
    stk->data = stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t);
    stk->data = NULL;
    
    return 0;
}

void stack_capacity_check(stack_t* stk) {
                               
    size_t data_size = 0;

    data_size = (size_t) (stk->capacity) * sizeof(stack_elem_t) + 2 * sizeof(unsigned long long);  

    if (stk->size >= stk->capacity) {
        
        data_size += 10 * sizeof(stack_elem_t);
        stk->data = (stack_elem_t*) realloc(stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t), data_size);  
        stk->data = stk->data + sizeof(unsigned long long) / sizeof(stack_elem_t);
        stk->capacity += 10;
        
        stk->data[stk->capacity] = stk->data[stk->capacity - 10];
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


