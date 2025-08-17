#ifndef STACK_STRUCTS_H
#define STACK_STRUCTS_H

#include <stdio.h>
#include <stdint.h>

#define HASH_PROTECT //TODO убрать перед релизом

#ifdef  HASH_PROTECT
#define IF_HASH(...) __VA_ARGS__
#define IF_ELSE_HASH(smth, other_smth) smth
#else /*HASH_PROTECT*/
#define IF_HASH(...)
#define IF_ELSE_HASH(smth, other_smth) other_smth
#endif /*HASH_PROTECT*/

/*====================STACK PARAMETERS========================*/
#define ALLOC_RESERVE       20                    //cells
#define DEFAULT_STR_LEN     50

#define MAX_STK_SIZE        1048576                  // 1 MB
#define ALIGNMENT           8                        // bytes, multiple of 8
#define CANARY_TYPE         uint64_t                 // must be multiple of 8

#define DATA_CAN_LEFT       (CANARY_TYPE) 0xDEDBABA
#define DATA_CAN_RIGHT      (CANARY_TYPE) 0xDEDDEAD
#define STRUCT_CAN_LEFT     (CANARY_TYPE) 0xCAFEBABE
#define STRUCT_CAN_RIGHT    (CANARY_TYPE) 0xDEADBEEF

#define MIN_STK_CAP         10
#define GROWTH_RATE         2                        // FALL_RATE > GROWTH_RATE (there os no
#define FALL_RATE           3                        // capacity shaking)
#define LINEAR_THR          100
#define SHRINK_GAP          20                       // SHRINK_GAP > ADDED_CELLS (there os no
#define ADDED_CELLS         10                       // capacity shaking)

#ifdef HASH_PROTECT
#define FNV_OFFSET_BASIS64 1469598103934665603ULL
#define FNV_PRIME64        1099511628211ULL
#endif /*HASH_PROTECT*/
/*============================================================*/

#define RAW_MEM_SIZE(cell_size, cell_num) cell_size * cell_num \
                             + align_up (sizeof(DATA_CAN_LEFT), ALIGNMENT)    \
                             + sizeof(DATA_CAN_RIGHT)

#define DATA_SIZE(cell_size, cell_num) cell_size * cell_num //TODO убрать если не пригодится

typedef struct {
    uint64_t struct_can_left;

    char name[DEFAULT_STR_LEN];
    
    void*  raw_mem;
    void*  data;
    
    size_t elem_size;
    size_t size;
    size_t capacity;
    size_t cell_size;
    
    CANARY_TYPE* data_can_right_ptr;

#ifdef HASH_PROTECT
    uint64_t struct_hash;
    uint64_t data_hash;
#endif /*HASH_PROTECT*/

    uint64_t struct_can_right;
} stack_t;

#endif //STACK_STRUCTS_H