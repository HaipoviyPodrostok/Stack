#ifndef STACK_CREATE_H
#define STACK_CREATE_H

#include "stack_structs.h"

int stack_ctor(stack_t* stk, int capacity); 
int stack_dtor(stack_t* stk); 
void stack_capacity_check(stack_t* stk);

#endif //STACK_CREATE_H