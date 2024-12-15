#include <stdio.h>
#include "stack_funcs.h"
#include "verificator.h"
#include "stack_create.h"

int stack_push(stack_t* stk, stack_elem_t value) {
    verificator(stk);
    
    stack_capacity_check(stk);

    stk->data[stk->size] = value;
    stk->size++;
    
    verificator(stk);
    return 0;
}

stack_elem_t stack_pop(stack_t* stk) {
    verificator(stk);

    stack_elem_t stack_peak = 0;
    
    stk->size--;
    
    verificator(stk);
    
    stack_peak = stk->data[stk->size];
    stk->data[stk->size] = 0;     

    verificator(stk);

    return stack_peak;
}
