#pragma once

#ifndef STL_H

#define STL_H

/*
 * stack 
 */
extern struct stack* stack_init(void* pval);
extern void* stack_pop(struct stack* stack);
extern void* stack_peek(struct stack* stack);
extern void stack_push(void* pval, stack* stack);

#endif // !STL_H
