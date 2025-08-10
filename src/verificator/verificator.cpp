#include <stdio.h>

#include "stack_structs.h"
#include "verificator.h"
#include "stack_err_handle.h"
#include "logger.h"
#include "stack_funcs.h"

// stack_err_t stack_verificator(stack_t* const stk) {
//     if (!stk) return STACK_ERR_NULL_PTR_ERROR;

//     if (stk->size > stk->capacity) return STACK_ERR_STK_OVERFLOW_ERROR;



// }

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
        "Right canary  %lx   (Expected: %lx)                                         \n",
        *((CANARY_TYPE*) (stk->raw_mem)),    left_canary,
        *((CANARY_TYPE*) (stk_data_offset(stk, stk->capacity))), right_canary);

    return STACK_ERR_SUCCESS;
}