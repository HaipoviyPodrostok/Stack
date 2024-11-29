#include <stdio.h>
#include "stack_funcs.h"

int main() {
    
    stack_t stack_1 = {};
    stack_constructor(&stack_1, 5);

    stack_elem_t stack_peak = 0;

    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);

    verificator(&stack_1);
    
    stack_peak = stack_pop(&stack_1);

    verificator(&stack_1);

    printf("%s:%s, %s(): stack_peak = %f\n", __FILE__, __FILE__, __func__, stack_peak);  

    stack_destructor(&stack_1);

    return 0;
}