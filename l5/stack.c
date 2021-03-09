#include "stack.h"

Stack *createStack(void (*destroyData)(void *data))
{
	return createDeque(destroyData);
}

void destroyStack(Stack *stack)
{
	destroyDeque(stack);
}

int isEmptyStack(Stack *stack)
{
	return isEmptyDeque(stack);
}

void push(Stack *stack, void *data)
{
	pushFront(stack,data);
}

void *pop(Stack *stack)
{
	return popFront(stack);
}

void *top(Stack *stack)
{
	return peekFront(stack);
}

void insert_at_bottom(Stack *stack, void *data)
{
	if (isEmptyStack(stack)){
		push(stack, data);
		return;
	}
	void *temp;
	temp = pop(stack);

	insert_at_bottom(stack,data);
	push(stack, temp);
}

void reverseStack(Stack *stack)
{
	if ( isEmptyStack(stack))
                return;
        void *data;
        data = pop(stack);
        reverseStack(stack);
        insert_at_bottom(stack, data);

}
