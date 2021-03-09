#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include <stdlib.h>

#define INF 10000

typedef struct heap_node {
	int priority;
	int data;
} HeapNode;

typedef struct {
	int size;
	int capacity;
	int *indexes;
	HeapNode *nodes;
} Heap;

Heap *createHeap(int capacity);

void destroyHeap(Heap *heap);

int isEmptyHeap(Heap *heap);

void insert(Heap *heap, int priority, int data);

int extract(Heap *heap);

void decreasePriority(Heap *heap, int priority, int data);

int inHeap(Heap *heap, int data);

int parent(int i);

int left(int i);

int right(int i);

void siftUp(Heap *heap, int i);

void siftDown(Heap *heap, int i);

#endif // HEAP_H_INCLUDED
