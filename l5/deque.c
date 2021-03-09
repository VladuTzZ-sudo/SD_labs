#include "deque.h"

Node *createNode(void *data)
{
	Node *node = malloc(sizeof(Node));

	if (node == NULL)
		return NULL;
	node->data = data;
	node->next = NULL;
	node->prev = NULL;
	return node;
}

void destroyNode(Node *node)
{
	free(node);
}

Deque *createDeque(void (*destroyData)(void *data))
{
	Deque *deque = malloc(sizeof(Deque));

	if (deque == NULL)
		return NULL;
	deque->size = 0;
	deque->destroyData = destroyData;
	deque->head = NULL;
	deque->tail = NULL;
	return deque;
}

void destroyDeque(Deque *deque)
{
	while (!isEmptyDeque(deque)) {
		deque->destroyData(peekFront(deque));
		popFront(deque);
	}
	free(deque);
}

int isEmptyDeque(Deque *deque)
{
	if (deque->head == NULL || deque->tail == NULL)
		return 1;
	return 0;
}

void pushBack(Deque *deque, void *data)
{
	Node *node = createNode(data);

	if (node == NULL)
		return;
	if (isEmptyDeque(deque)) {
		deque->head = node;
		deque->tail = node;
	} else {
		deque->tail->next = node;
		node->prev = deque->tail;
		deque->tail = node;
	}
	deque->size++;
}

void *popBack(Deque *deque)
{
	Node *node;
	void *data;

	if (isEmptyDeque(deque))
		return NULL;
	node = deque->tail;
	data = node->data;
	deque->tail = deque->tail->prev;
	if (!isEmptyDeque(deque))
		deque->tail->next = NULL;
	destroyNode(node);
	deque->size--;
	return data;
}

void *peekBack(Deque *deque)
{
	if (isEmptyDeque(deque))
		return NULL;
	return deque->tail->data;
}

void pushFront(Deque *deque, void *data)
{
	Node *node = createNode(data);

	if (node == NULL)
		return;
	if (isEmptyDeque(deque)) {
		deque->head = node;
		deque->tail = node;
	} else {
		deque->head->prev = node;
		node->next = deque->head;
		deque->head = node;
	}
	deque->size++;
}

void *popFront(Deque *deque)
{
	Node *node;
	void *data;

	if (isEmptyDeque(deque))
		return NULL;
	node = deque->head;
	data = node->data;
	deque->head = deque->head->next;
	if (!isEmptyDeque(deque))
		deque->head->prev = NULL;
	destroyNode(node);
	deque->size--;
	return data;
}

void *peekFront(Deque *deque)
{
	if (isEmptyDeque(deque))
		return NULL;
	return deque->head->data;
}
