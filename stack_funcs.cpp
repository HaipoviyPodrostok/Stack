#include <stdio.h>
#include "stack_funcs.h"

int stack_push(stack* stk, stack_elem value) {
    verificator(stk);
    
    stk->data = stack_capacity_check(stk);

    stk->data[stk->size] = value;
    stk->size++;
    
    verificator(stk);
    return(0);
}

stack_elem stack_pop(stack* stk) {
    verificator(stk);

    stack_elem stack_peak = 0;
    
    stk->size--;
    
    verificator(stk);
    
    stack_peak = stk->data[stk->size];

    verificator(stk);

    return stack_peak;
}

