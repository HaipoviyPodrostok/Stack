#include <stdio.h>
#include "stack_structs.h"
#include "stack_create.h"
#include "stack_funcs.h"
#include "verificator.h"

int main() {
    
    stack_t stack_1 = {};
    stack_ctor(&stack_1, 5);

    stack_elem_t stack_peak = 0;

    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_push(&stack_1, 3);
    stack_push(&stack_1, 5);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);
    stack_pop(&stack_1);

    verificator(&stack_1);
    
    stack_peak = stack_pop(&stack_1);

    verificator(&stack_1);

    printf("%s:%s, %s(): stack_peak = %f\n", __FILE__, __FILE__, __func__, stack_peak);  

    stack_dtor(&stack_1);

    stack_push(&stack_1, 5);

    return 0;
}