#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "deque.h"

typedef Deque Stack;

Stack *createStack(void (*destroyData)(void *data));

void destroyStack(Stack *stack);

int isEmptyStack(Stack *stack);

void push(Stack *stack, void *data);

void *pop(Stack *stack);

void *top(Stack *stack);

void reverseStack(Stack *stack);

#endif /* STACK_H_INCLUDED */
