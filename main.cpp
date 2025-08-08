#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "stack_structs.h"
#include "stack_funcs.h"

int main() {
    LOGGER_ERROR(log_open("ctor.log"));
    
    stack_t stack = {};

    typedef struct {
        int gei;
        double pidor;
        size_t hui;
    } cell_t;

    STACK_ERROR(stack_ctor(&stack, "stack 1", sizeof(cell_t), 10));
    
    cell_t first_cell = {};
    first_cell.gei = 10;
    first_cell.pidor = 10.11;
    first_cell.hui = 20;
    
    STACK_ERROR(stack_push(&stack, &first_cell));

    
    cell_t popa = {};

    stack_pop(&stack, &popa);
    printf("%d\n", popa.gei);
    printf("%lg\n", popa.pidor);
    printf("%lu\n", popa.hui);

    stack_dtor(&stack);
    
    log_close();

    return 0;
}