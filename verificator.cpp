#include <stdio.h>
#include <cstdlib>
#include "verificator.h"

int stack_check(stack* stk) {
    
    if (stk == NULL) {
        return ERROR_NULL_POINTER;
    } 

    if (stk->size < 0) {
        return ERROR_NEGATIVE_SIZE;
    }

    if (stk->capacity < 0) {
        return ERROR_NEGATIVE_CAPACITY;
    }

    if (stk->size >= stk->capacity) {
        return ERROR_SIZE_OVERFLOW;
    }

    return 0;
}

void stack_dump(stack* stk) {
    print_error(stk);
    printf("stack_data %p\n", (stk->data));
    printf("stack_size %d\n", (stk->size));
    printf("stack_capacity %d\n", (stk->capacity));
}

int verificator(stack* stk) {
    
    if (stack_check(stk) != 0) {
        stack_dump(stk);
        abort();
    }

    return 0;
}

void print_error(stack* stk) {
    int error_num = 0;
    error_num = stack_check(stk);

    if (error_num == ERROR_NULL_POINTER) {
        printf("ERROR_NULL_POINTER\n");
    }

    if (error_num == ERROR_NEGATIVE_SIZE) {
        printf("ERROR_NEGATIVE_SIZE\n");
    }

    if (error_num == ERROR_NEGATIVE_CAPACITY) {
        printf("ERROR_NEGATIVE_CAPACITY\n");
    }

    if (error_num == ERROR_SIZE_OVERFLOW) {
        printf("ERROR_SIZE_OVERFLOW\n");
    }
}
