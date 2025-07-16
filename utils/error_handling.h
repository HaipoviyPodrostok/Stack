#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <stdio.h>

#define ERROR_HANDLE(call_func, ...) ({                                             \
    stack_err_t error = call_func;                                                  \
    if (error) {                                                                    \
        fprintf(stderr, "[" #call_func "] Error: %s\n", tree_error_str(error));     \
        __VA_ARGS__;                                                                \
        return error;                                                               \
    }                                                                               \
});

typedef enum {
    STACK_ERR_SUCCES = 0,
    STACK_ERR_DUMP_FAILED = 1,
    STACK_ERR_ALLOCATION_FAILED = 2,
    STACK_ERR_FILE_READING_FAILED = 3,
    STACK_ERR_FILE_OPEN_FAILED = 4,
    STACK_ERR_FILE_PRINT_FAILED = 5,
    STACK_ERR_NULL_PTR_ERROR = 6,
    STACK_ERR_FILE_CLOSE_FAILED = 7,
    STACK_ERR_STR_PRINT_FAILED = 8,
    STACK_ERR_INSERTION_FAILED = 9,
    STACK_ERR_INPUT_FILE_INCORRECT = 10,
    STACK_ERR_FILL_NODE_FAILED = 11,
    STACK_ERR_INPUT_SCAN_FAILED = 12,
    STACK_ERR_TOO_FEW_COMMAND_LINE_ARGUMENTS = 13,
    STACK_ERR_UNKNOWN_ERROR = 14,
    STACK_ERR_INCORRECT_STATUS = 15,
} stack_err_t;

bool isEqual (double x, double y);

#endif //ERROR_HANDLING_H