#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

typedef double stack_elem_t;

typedef struct Stack {
    stack_elem_t* data;
    int size;
    int capacity;
} stack_t;

#endif //STACK_STRUCTS_H
