#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>

#define ALLOC_RESERVE 20 //cells
#define DEFAULT_STR_LEN 50 

#define ALIGNMENT 8 //bytes, multiple of 8
#define CELL_SIZE(elem_size) ((elem_size + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT

#define CANARY_TYPE unsigned long long
#define LEFT_CANARY (CANARY_TYPE) 0xDEDBABA
#define RIGHT_CANARY  (CANARY_TYPE) 0xDEDDEAD

#define DATA_SIZE(cell_num) stk->cell_size * cell_num \
                             + sizeof(LEFT_CANARY)    \
                             + sizeof(RIGHT_CANARY)

typedef struct {
    char name[DEFAULT_STR_LEN];
    void* raw_mem;
    void* data;
    size_t elem_size;
    size_t size;
    size_t capacity;
    size_t cell_size;
} stack_t;




#endif //STACK_STRUCTS_H