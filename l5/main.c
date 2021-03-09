#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "deque.h"
#include "queue.h"
#include "stack.h"

void destroyNothing(void *data)
{
	/* Static allocated vars shall not be freed. */
	if (data == NULL)
		return;
}

void (*destroyInt)(void *data) = destroyNothing;
void (*destroyChar)(void *data) = destroyNothing;

int checkBalanced(char *str)
{
	return 0;
}

void testCheckBalanced(void)
{
	printf("%d == 1?\n", checkBalanced("{((())(([]))(()))(())}()"));
	printf("%d == 0?\n", checkBalanced("{((())((]))(()))(())}()"));
	printf("%d == 0?\n", checkBalanced("{((())(([))(()))(())}()"));
	printf("%d == 0?\n", checkBalanced("{((())(([]))(()))(())}("));
	printf("%d == 0?\n", checkBalanced("{((())(([]))(()))(())})"));
	printf("%d == 0?\n", checkBalanced("{})"));
	printf("%d == 0?\n", checkBalanced("{}("));
	printf("%d == 0?\n", checkBalanced(")"));
	printf("%d == 0?\n", checkBalanced("("));
	printf("%d == 1?\n", checkBalanced("{}"));
	printf("%d == 0?\n", checkBalanced("}{"));
	printf("%d == 1?\n", checkBalanced(""));
}

int main(void)
{
	/* TODO: Create a stack with some numbers and reverse it. */
    /* Print the stack before and after reversing. */

	/* TODO: Create a queue with some numbers and reverse it. */
    /* Print the queue before and after reversing. */

	/* TODO: testCheckBalanced */

	/* TODO: What has valgrind (or checkpatch) to say about it? */

        int v[]={3, 4, 5, 6, 7};
	int i;
	Stack *stack;
	stack = createStack(destroyInt);
	for ( i = 0; i < sizeof(v) / sizeof(v[0]); i++ ){
		push(stack, &v[i]);
	}
	void *data;	
	while( !isEmptyStack(stack) ) {
		data = pop(stack);
		printf("%d\n", *(int *)data);
	}
	destroyStack(stack);

	printf("\n");

	char str[]="paralelipiped";
	Queue *queue;
	queue = createQueue(destroyInt);
	for ( i = 0; i < sizeof(str) / sizeof(str[0]); i++ ){
		enqueue(queue, &str[i]);
	}
	reverseQueue(queue);
	while(!isEmptyStack(queue)){
		printf("%c\n", *(char *)dequeue(queue));
	}
	destroyStack(stack);
	return 0;
}
