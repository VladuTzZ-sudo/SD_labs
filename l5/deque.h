#ifndef DEQUE_H_INCLUDED
#define DEQUE_H_INCLUDED

#include <stdlib.h>

typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;
} Node;

typedef struct {
	long size;
	void (*destroyData)(void *data);
	Node *head;
	Node *tail;
} Deque;

Node *createNode(void *data);

void destroyNode(Node *node);

Deque *createDeque(void (*destroyData)(void *data));

void destroyDeque(Deque *deque);

int isEmptyDeque(Deque *deque);

void pushBack(Deque *deque, void *data);

void *popBack(Deque *deque);

void *peekBack(Deque *deque);

void pushFront(Deque *deque, void *data);

void *popFront(Deque *deque);

void *peekFront(Deque *deque);

#endif /* DEQUE_H_INCLUDED */
