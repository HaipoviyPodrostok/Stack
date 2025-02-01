    #ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

typedef double stack_elem_t;

typedef struct Stack {
    stack_elem_t* data;
    int size;
    int capacity;
} stack_t;

enum INPUT_ACTIONS {
    PUSH = 1,
    POP = 2,
    VERIFICATOR = 3,
    STACK_DUMP = 4,
    EXIT = 5,
};

#endif //STACK_STRUCTS_H
