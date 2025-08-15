#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>


/*====================STACK PARAMETERS========================*/
#define ALLOC_RESERVE   20                    //cells
#define DEFAULT_STR_LEN 50

#define MAX_STK_SIZE    1048576                  // 1 MB
#define ALIGNMENT       8                        // bytes, multiple of 8
#define CANARY_TYPE     unsigned long long       // must be multiple of 8
#define LEFT_CANARY     (CANARY_TYPE) 0xDEDBABA
#define RIGHT_CANARY    (CANARY_TYPE) 0xDEDDEAD
#define MIN_STK_CAP     10
#define GROWTH_RATE     2                        // FALL_RATE > GROWTH_RATE (there os no
#define FALL_RATE       3                        // capacity shaking)
#define LINEAR_THR      100
#define SHRINK_GAP      20                       // SHRINK_GAP > ADDED_CELLS (there os no
#define ADDED_CELLS     10                       // capacity shaking)
/*============================================================*/

#define RAW_MEM_SIZE(cell_size, cell_num) cell_size * cell_num \
                             + align_up (sizeof(LEFT_CANARY), ALIGNMENT)    \
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