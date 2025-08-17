#ifndef STACK_ERR_HANDLE_H
#define STACK_ERR_HANDLE_H

#include <stdio.h>

#define STACK_ERROR(call_func, ...) ({                                                                \
    stack_err_t error = call_func;                                                                    \
    if (error) {                                                                                      \
        fprintf(stderr, "%s:%d, "#call_func": %s\n", __FILE__, __LINE__, stack_error_str(error));    \
        LOG(ERROR, LOG_INFO, " %s", stack_error_str(error));                                          \
        __VA_ARGS__;                                                                                  \
        return error;                                                                                 \
    }                                                                                                 \
});

typedef enum {
    STACK_ERR_SUCCESS = 0,
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
    STACK_ERR_INCORRECT_CELL_SIZE = 16,
    STACK_ERR_TOO_SMALL_CAPACITY = 17,
    STACK_ERR_STK_REALLOC_FAILED = 18,
    STACK_ERR_STK_OVERFLOW_ERROR = 19,
    STACK_ERR_STK_IS_TOO_BIG = 20,
    STACK_ERR_NOWHERE_TO_EXPAND = 21,
    STACK_ERR_INVALID_STRUCT = 22,
    STACK_ERR_DATA_CANARIES_ARE_CORRUPTED = 23,
    STACK_ERR_STRUCT_CANARIES_ARE_CORRUPTED = 24,
    STACK_ERR_ALIGN_IS_BROKEN = 25,
    STACK_ERR_STRUCT_HASH_ERROR = 26,
    STACK_ERR_DATA_HASH_ERROR = 27,
} stack_err_t;

const char* stack_error_str(stack_err_t error);

#endif //STACK_ERR_HANDLE_H