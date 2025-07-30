#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>

#define ALLOC_RESERVE 10 //cells

#define CELL_SIZE 8 //bytes

#define CANNARY_TYPE unsigned long long
#define FIRST_CANNARY (CANNARY_TYPE) 0xDEDBABA
#define LAST_CANNARY  (CANNARY_TYPE) 0xDEDDEAD

typedef struct {
    void* raw_mem;
    void* data;
    size_t elem_size;
    size_t size;
    size_t capacity;
} stack_t;




#endif //STACK_STRUCTS_H