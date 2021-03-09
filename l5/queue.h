#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include "deque.h"

typedef Deque Queue;

Deque *createQueue(void (*destroyData)(void *data));

void destroyQueue(Queue *queue);

int isEmptyQueue(Queue *queue);

void enqueue(Queue *queue, void *data);

void *dequeue(Queue *queue);

void *front(Queue *queue);

void reverseQueue(Queue *queue);

#endif /* QUEUE_H_INCLUDED */
