#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>

#define ALLOC_RESERVE 10
#define CANNARY_TYPE unsigned long long
#define FIRST_CANNARY 0xDEDBABA
#define LAST_CANNARY 0xDEDDEAD

typedef struct {
    void* raw_mem;
    void* data;
    size_t elem_size;
    size_t size;
    size_t capacity;
} stack_t;




#endif //STACK_STRUCTS_H