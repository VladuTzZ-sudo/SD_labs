#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "../deque/deque.h"

typedef Deque Stack;

Stack *createStack();

void destroyStack(Stack *stack);

int isEmptyStack(Stack *stack);

void push(Stack *stack, int data);

int pop(Stack *stack);

int top(Stack *stack);

#endif /* STACK_H_INCLUDED */
