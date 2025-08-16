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

    size_t left_canary  = *((CANARY_TYPE*) (stk->raw_mem));
    size_t right_canary = *((CANARY_TYPE*) (stk_data_offset(stk, stk->capacity)));
    
    if (left_canary  != LEFT_CANARY ||
        right_canary != RIGHT_CANARY) {
            stack_dump(stk);
            return STACK_ERR_CANARIES_ARE_CORRUPTED;
    }

    if (!is_aligned(stk->raw_mem, ALIGNMENT)           ||
        !is_aligned(stk->data,    ALIGNMENT)           ||
        !is_aligned(stk->right_canary_ptr, ALIGNMENT)) { 
            stack_dump(stk);
            return STACK_ERR_ALIGN_IS_BROKEN;
        }

    if (RAW_MEM_SIZE(stk->cell_size, stk->capacity) >= MAX_STK_SIZE) {
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

    size_t left_canary  = LEFT_CANARY;
    size_t right_canary = RIGHT_CANARY;
    
        LOG(INFO, NO_LOG_INFO,
        "Left canary:  %lx   (Expected: %lx)                                         \n"
        "Right canary  %lx   (Expected: %lx)                                         \n"
        "============================================================================\n",
        *((CANARY_TYPE*) (stk->raw_mem)),    left_canary,
        *((CANARY_TYPE*) (stk_data_offset(stk, stk->capacity))), right_canary);

    return STACK_ERR_SUCCESS;
}

static bool is_aligned(const void* ptr, const size_t align) {
    return ((uintptr_t) ptr % align) == 0;
}