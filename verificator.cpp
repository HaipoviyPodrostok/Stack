#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include "verificator.h"

int verificator(const stack_t* stk) {
    
    if (stack_check(stk) != 0) {
        stack_dump(stk);
        abort();
    }

    return 0;
}

int stack_check(const stack_t* stk) {
    
    if (stk == NULL) {
        return ERROR_STACK_NULL_POINTER;      
    } 

    if (stk->data == NULL) {
        return ERROR_DATA_NULL_POINTER;
    }

    if (stk->size < 0) {
        return ERROR_NEGATIVE_SIZE;
    }

    if (stk->capacity < 0) {
        return ERROR_NEGATIVE_CAPACITY;
    }

    if (stk->size > stk->capacity) {
        return ERROR_SIZE_OVERFLOW;
    }

    if (int(*(stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t))) != 0xDEDBABA) {   //*((unsigned long long*) (stk->data - sizeof(unsigned long long) / sizeof(stack_elem_t)))
        return ERROR_STACK_CANARY_BEGINING;
    }

    if (int((stk->data[stk->capacity])) !=  0xDEDDEAD) {
        return ERROR_STACK_CANARY_END;
    }

    return 0;
}

void stack_dump(const stack_t* stk) {
    print_error(stk);
    printf("*******STACK DUMP*********\n");
    printf("    stack_data: %p\n", (stk->data));
    printf("    stack_size: %d\n", (stk->size));
    printf("    stack_capacity: %d\n", (stk->capacity));
}

void print_error(const stack_t* stk) {
    int error_num = 0;    
    error_num = stack_check(stk);

    switch (error_num) {
    
        case ERROR_STACK_NULL_POINTER:
            printf("ERROR_STACK_NULL_POINTER\n");
            break;
        
        case ERROR_DATA_NULL_POINTER:
            printf("ERROR_DATA_NULL_POINTER\n");
            break;

        case ERROR_NEGATIVE_SIZE:
            printf("ERROR_NEGATIVE_SIZE\n");
            break;

        case ERROR_NEGATIVE_CAPACITY:
            printf("ERROR_NEGATIVE_CAPACITY\n");
            break;

        case ERROR_SIZE_OVERFLOW:
            printf("ERROR_SIZE_OVERFLOW\n");
            break;

        case ERROR_STACK_CANARY_BEGINING:
            printf("ERROR_STACK_CANARY_BEGINING\n");
            break;

        case ERROR_STACK_CANARY_END:
            printf("ERROR_STACK_CANARY_END\n");
            break;
        
        default:
            ;
    }
}



