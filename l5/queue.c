#include "queue.h"

Deque *createQueue(void (*destroyData)(void *data))
{
	return createDeque(destroyData);
}

void destroyQueue(Queue *queue)
{
	destroyDeque(queue);
}

int isEmptyQueue(Queue *queue)
{
	return isEmptyDeque(queue);
}

void enqueue(Queue *queue, void *data)
{
	pushBack(queue, data);
}

void *dequeue(Queue *queue)
{
	return popFront(queue);
}

void *front(Queue *queue)
{
	return peekFront(queue);
}

void reverseQueue(Queue *queue)
{
	if ( isEmptyQueue(queue))
		return;
	void *data;
        data = dequeue(queue);
	reverseQueue(queue);
	enqueue(queue, data);
}
