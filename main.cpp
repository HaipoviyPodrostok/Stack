#include <stdio.h>
#include "stack_funcs.h"

int main() {
    
    stack stack_1;
    stack_constructor(&stack_1, 5);

    stack_elem stack_peak = 0;

    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);

    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);
    stack_peak = stack_pop(&stack_1);

    printf("%f", stack_peak);  

    stack_distructor(&stack_1);

    return 0;
}