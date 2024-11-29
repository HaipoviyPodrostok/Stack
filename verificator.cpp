#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "verificator.h"

int stack_check(const stack_t* stk) {
    
    if (stk == NULL) {
        return ERROR_STACK_NULL_POINTER;      
    } 

    if (stk->data == NULL) {
        return ERROR_DATA_NULL_POINTER;
    }

    if (stk->size < 1) {
        return ERROR_NEGATIVE_SIZE;
    }

    if (stk->capacity < 1) {
        return ERROR_NEGATIVE_CAPACITY;
    }

    if (stk->size > stk->capacity) {
        return ERROR_SIZE_OVERFLOW;
    }

    if (!isEqual(stk->data[0], 0xDEDBABA)) {
        return ERROR_STACK_CANARY_BEGINING;
    }

    if (!isEqual(stk->data[stk->capacity], 0xDEDDEAD)) {
        return ERROR_STACK_CANARY_END;
    }

    return 0;
}

void stack_dump(const stack_t* stk) {
    print_error(stk);
    printf("stack_data: %p\n", (stk->data));
    printf("stack_size: %d\n", (stk->size));
    printf("stack_capacity: %d\n", (stk->capacity));
}

int verificator(const stack_t* stk) {
    
    if (stack_check(stk) != 0) {
        stack_dump(stk);
        abort();
    }

    return 0;
}

void print_error(const stack_t* stk) {
    int error_num = 0;
    error_num = stack_check(stk);

    if (error_num == ERROR_STACK_NULL_POINTER) {
        printf("ERROR_STACK_NULL_POINTER\n");
    }
    
    if (error_num == ERROR_DATA_NULL_POINTER) {
        printf("ERROR_DATA_NULL_POINTER\n");
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

    if (error_num == ERROR_STACK_CANARY_BEGINING) {
        printf("ERROR_STACK_CANARY_BEGINING\n");
    }

    if (error_num == ERROR_STACK_CANARY_END) {
        printf("ERROR_STACK_CANARY_END\n");
    }
}

bool isEqual (double x, double y) {
    const double EPSILON = 1e-6;
    return fabs (x - y) < EPSILON;
}




