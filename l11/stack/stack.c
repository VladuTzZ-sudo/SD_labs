#include "stack.h"

Stack *createStack()
{
	return createDeque();
}

void destroyStack(Stack *stack)
{
	destroyDeque(stack);
}

int isEmptyStack(Stack *stack)
{
	return isEmptyDeque(stack);
}

void push(Stack *stack, int data)
{
	pushFront(stack, data);
}

int pop(Stack *stack)
{
	return popFront(stack);
}

int top(Stack *stack)
{
	return peekFront(stack);
}
