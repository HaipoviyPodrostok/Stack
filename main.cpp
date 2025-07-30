#include <stdio.h>
#include <stdlib.h>

#include "logger.h"
#include "stack_structs.h"
#include "stack_funcs.h"

int main() {   //makefile поменять чтобы можно было менять проект/библиотека
    LOGGER_ERROR(log_open("log/ctor.log"));
    
    stack_t stack = {};

    STACK_ERROR(stack_ctor(&stack, 4, 10));
    
    int value = 10;
    STACK_ERROR(stack_push(&stack, &value));
    value = 0;
    
    int peak = 0;
    STACK_ERROR(stack_pop(&stack, &peak));

    stack_dtor(&stack);
    
    log_close();

    return 0;
}