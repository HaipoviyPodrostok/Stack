#include "stack_funcs.h"

#define CELL_SIZE(elem_size) ((elem_size + ALIGNMENT - 1) / ALIGNMENT) * ALIGNMENT

static stack_err_t stack_overflow_check(stack_t* stk);
static stack_err_t realloc_stack_init(stack_t* stk, const size_t new_capacity);

stack_err_t stack_ctor(stack_t* const stk,     const char* stk_name,
                       const size_t elem_size, const size_t capacity) {
    if (!stk)                   return STACK_ERR_NULL_PTR_ERROR;
    if (elem_size == 0)         return STACK_ERR_INCORRECT_CELL_SIZE;
    if (capacity < MIN_STK_CAP) return STACK_ERR_TOO_SMALL_CAPACITY;

    strncpy(stk->name, stk_name, DEFAULT_STR_LEN);
    stk->name[DEFAULT_STR_LEN - 1] = '\0';
    
    stk->size      = 0;
    stk->elem_size = elem_size;
    stk->capacity  = capacity;
    stk->cell_size = CELL_SIZE(elem_size);

    const size_t raw_mem_size = RAW_MEM_SIZE(stk->cell_size, stk->capacity);
    if (raw_mem_size > MAX_STK_SIZE) return STACK_ERR_STK_IS_TOO_BIG;

    stk->raw_mem = calloc(1, raw_mem_size);  //first canary ptr
    if (!stk->raw_mem) return STACK_ERR_ALLOCATION_FAILED;
    stk->data = (void*) ((char*) stk->raw_mem + sizeof(CANARY_TYPE));

    *((CANARY_TYPE*) stk->raw_mem) = DATA_CAN_LEFT;
    
    stk->data = (void*) ((char*) stk->raw_mem 
                               + align_up(sizeof(CANARY_TYPE), ALIGNMENT));

    stk->data_can_right_ptr  = (CANARY_TYPE*) stk_data_offset(stk, stk->capacity);
    *stk->data_can_right_ptr = DATA_CAN_RIGHT;

    return STACK_ERR_SUCCESS;
}

void stack_dtor(stack_t* const stk) {
    free(stk->raw_mem);

    stk->size = 0;
    stk->capacity = 0;
    stk->elem_size = 0;
    stk->data = NULL;
    stk->raw_mem = NULL;

    return;
}

stack_err_t stack_push(stack_t* const stk, const void* const value) {
    if (!stk) return STACK_ERR_NULL_PTR_ERROR;
    
    STACK_ERROR(stack_verificator(stk), stack_dtor(stk));

    stack_err_t overflow_check_result = stack_overflow_check(stk);

    if (overflow_check_result != STACK_ERR_SUCCESS &&
        overflow_check_result != STACK_ERR_NOWHERE_TO_EXPAND) {
        return STACK_ERR_STK_REALLOC_FAILED;
    }

    if (overflow_check_result == STACK_ERR_NOWHERE_TO_EXPAND) {
        LOG(WARNING, LOG_INFO, "It is impossible to add an element: "
            "the stack has reached its maximum size.");
        return STACK_ERR_NOWHERE_TO_EXPAND;
    }

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(stk_peak, value, stk->elem_size);

    void* padding = (void*) ((char*) stk_peak + stk->elem_size);
    assert(stk->elem_size <= stk->cell_size);
    memset(padding, 0xCC, (stk->cell_size - stk->elem_size));

    stk->size++;

    STACK_ERROR(stack_verificator(stk), stack_dtor(stk));

    return STACK_ERR_SUCCESS;
}

stack_err_t stack_pop(stack_t* const stk, void* const value) {
    if (!stk || !value) return STACK_ERR_NULL_PTR_ERROR;
    
    STACK_ERROR(stack_verificator(stk), stack_dtor(stk));

    stk->size--;

    void* stk_peak = stk_data_offset(stk, stk->size);
    memcpy(value, stk_peak, stk->elem_size);

    memset(stk_peak, 0, stk->elem_size);

    STACK_ERROR(stack_verificator(stk), stack_dtor(stk));

    return STACK_ERR_SUCCESS;
}

void* stk_data_offset(const stack_t* const stk, const size_t offset_size) {
    char* base = (char*) stk->data;
    return base + offset_size * stk->cell_size;
}

static stack_err_t stack_overflow_check(stack_t* stk) {
    assert(stk);

    size_t new_capacity = 0;
    size_t old_capacity = stk->capacity;

    if (old_capacity >= MIN_STK_CAP) {
        if (old_capacity <= LINEAR_THR) {                      // Threshold of linear/exponential growth
            if (stk->size >= stk->capacity) {
                new_capacity = old_capacity + ADDED_CELLS;
                if (RAW_MEM_SIZE(stk->cell_size, new_capacity) > MAX_STK_SIZE) {
                    new_capacity = old_capacity;
                    if (stk->size >= new_capacity) return STACK_ERR_NOWHERE_TO_EXPAND;
                }
                return realloc_stack_init(stk, new_capacity);
            }
            if ((stk->capacity - stk->size) >= SHRINK_GAP) {
                new_capacity = old_capacity - ADDED_CELLS;
                if (new_capacity < stk->size) {
                    new_capacity = stk->size;
                }
                if (new_capacity < MIN_STK_CAP) {
                    new_capacity = MIN_STK_CAP;
                }
                return realloc_stack_init(stk, new_capacity);
            }
        } else {
            if (stk->size >= stk->capacity) {
                new_capacity = old_capacity * GROWTH_RATE;
                if (RAW_MEM_SIZE(stk->cell_size, new_capacity) > MAX_STK_SIZE) {
                    new_capacity = old_capacity;
                    if (stk->size >= new_capacity) return STACK_ERR_NOWHERE_TO_EXPAND;
                }
                return realloc_stack_init(stk, new_capacity);
            }
            if (old_capacity >= GROWTH_RATE * stk->size) {
                new_capacity = old_capacity / GROWTH_RATE;          
                if (new_capacity < stk->size) {
                    new_capacity = stk->size;
                }
                if (new_capacity < MIN_STK_CAP) {
                    new_capacity = MIN_STK_CAP;
                }
                return realloc_stack_init(stk, new_capacity);
            } 
        }
    }

    return STACK_ERR_SUCCESS;
}

static stack_err_t realloc_stack_init(stack_t* stk, const size_t new_capacity) {
    assert(stk);

    if (new_capacity != stk->capacity) {
        void* new_raw_mem = NULL;

        new_raw_mem = realloc(stk->raw_mem, RAW_MEM_SIZE(stk->cell_size, new_capacity));
        if (!new_raw_mem) return STACK_ERR_ALLOCATION_FAILED;
        stk->raw_mem = new_raw_mem;

        stk->capacity = new_capacity;
        
        *((CANARY_TYPE*) stk->raw_mem) = DATA_CAN_LEFT;
        
        stk->data = (void*) ((char*) stk->raw_mem 
        + align_up(sizeof(CANARY_TYPE), ALIGNMENT));
        
        stk->data_can_right_ptr  = (CANARY_TYPE*) stk_data_offset(stk, stk->capacity);
        *stk->data_can_right_ptr = DATA_CAN_RIGHT;
    }

    return STACK_ERR_SUCCESS;
}

size_t align_up(size_t size, size_t align) {
    return (size + (align - 1)) & ~(align - 1);
}