#include <stdio.h>

#include "stack_structs.h"
#include "verificator.h"
#include "stack_err_handle.h"
#include "logger.h"
#include "stack_funcs.h"

static bool is_aligned(const void* ptr, const size_t align);

stack_err_t stack_verificator(stack_t* const stk) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;

    if (stk->raw_mem   == NULL          ||
        stk->data      == NULL          ||
        stk->elem_size == 0             || 
        stk->elem_size % ALIGNMENT != 0 ||
        stk->capacity  < stk->size      ||
        stk->capacity < MIN_STK_CAP     ) {
            stack_dump(stk);
            return STACK_ERR_INVALID_STRUCT;
    }

    size_t data_can_left  = *((CANARY_TYPE*) (stk->raw_mem));
    size_t data_can_right = *stk->data_can_right_ptr;
    
    if (data_can_left  != DATA_CAN_LEFT ||
        data_can_right != DATA_CAN_RIGHT) {
            stack_dump(stk);
            return STACK_ERR_DATA_CANARIES_ARE_CORRUPTED;
    }

    if (stk->struct_can_left  != STRUCT_CAN_LEFT ||
        stk->struct_can_right != STRUCT_CAN_RIGHT) {
            stack_dump(stk);
            return STACK_ERR_STRUCT_CANARIES_ARE_CORRUPTED;
        }

    if (!is_aligned(stk->raw_mem, ALIGNMENT)           ||
        !is_aligned(stk->data,    ALIGNMENT)           ||
        !is_aligned(stk->data_can_right_ptr, ALIGNMENT)) { 
            stack_dump(stk);
            return STACK_ERR_ALIGN_IS_BROKEN;
        }

    if (RAW_MEM_SIZE(stk->cell_size, stk->capacity) >= MAX_STK_SIZE) {
        stack_dump(stk);
        return STACK_ERR_STK_OVERFLOW_ERROR;
    }
    return STACK_ERR_SUCCESS;
}

stack_err_t stack_dump(stack_t* const stk) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;

    LOG(INFO, LOG_INFO, "\n"
        "============================== STACK DUMP =================================\n"
        "Stack name:   %s                                                           \n"
        "Stack ptr:    %p                                                           \n"
        "Raw mem:      %p                                                           \n"
        "Data:         %p                                                           \n"
        "Elem size:    %lu                                                          \n"
        "Current size: %lu                                                          \n" 
        "Capacity:     %lu                                                          \n"
        "Cell size:    %lu                                                          \n",
        
        stk->name,
        stk,
        stk->raw_mem,
        stk->data,
        stk->elem_size,
        stk->size,
        stk->capacity,
        stk->cell_size );

    size_t data_can_left    = DATA_CAN_LEFT;
    size_t data_can_right   = DATA_CAN_RIGHT;
    size_t struct_can_left  = STRUCT_CAN_LEFT;
    size_t struct_can_right = STRUCT_CAN_RIGHT; 

    LOG(INFO, NO_LOG_INFO,
        "Left data canary:  %lx   (Expected: %lx)                                    \n"
        "Right data canary  %lx   (Expected: %lx)                                    \n",
        *((CANARY_TYPE*) (stk->raw_mem)),    data_can_left,
        *((CANARY_TYPE*) (stk_data_offset(stk, stk->capacity))), data_can_right);

    LOG(INFO, NO_LOG_INFO,
        "Left data canary:  %lx   (Expected: %lx)                                    \n"
        "Right data canary  %lx   (Expected: %lx)                                    \n"
        "============================================================================\n",
        stk->struct_can_left,  struct_can_left,
        stk->struct_can_right, struct_can_right);

    return STACK_ERR_SUCCESS;
}

static bool is_aligned(const void* ptr, const size_t align) {
    return ((uintptr_t) ptr % align) == 0;
}

static uint64_t stack_hash(const void* adr, size_t len, uint64_t seed) {
    const unsigned char* p = (const unsigned char*) adr;
    uint64_t h = seed;
    for (size_t i = 0; i < len; i++) {
        h = h * 131u + p[i];
    }
    return h;
}
