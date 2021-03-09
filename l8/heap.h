#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

typedef struct {
	int content;
	int prior;
} ItemType;

typedef struct heap {
    long int capacity;
    long int size;
    ItemType *elem;
} PriorityQueue;

PriorityQueue *makeQueue(int capacity);

int getLeftChild(int i);

int getRightChild(int i);

int getParent(int i);

void siftUp(PriorityQueue *h, int idx);

void insert(PriorityQueue *h, ItemType x);

ItemType getMin(PriorityQueue *h);

void siftDown(PriorityQueue *h, int idx);

ItemType removeMin(PriorityQueue *h);

#endif
