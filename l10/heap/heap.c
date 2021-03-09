#include "heap.h"

void swap(void *a, void *b, size_t len)
{
    unsigned char *p = a, *q = b, tmp;
    for (size_t i = 0; i != len; i++)
    {
        tmp = p[i];
        p[i] = q[i];
        q[i] = tmp;
    }
}

Heap *createHeap(int capacity)
{
	Heap *heap = malloc(sizeof(Heap));

	if (heap == NULL)
		return NULL;
	heap->size = 0;
	heap->capacity = capacity;
	heap->indexes = malloc(capacity * sizeof(int));
	heap->nodes = malloc(capacity * sizeof(HeapNode));
	return heap;
}

void destroyHeap(Heap *heap)
{
	free(heap->nodes);
	free(heap);
}

int isEmptyHeap(Heap *heap)
{
	return !heap->size;
}

void insert(Heap *heap, int priority, int data)
{
	if (heap->size == heap->capacity)
		return;
    heap->indexes[data] = heap->size;
    heap->nodes[heap->size].priority = priority;
    heap->nodes[heap->size].data = data;
    heap->size++;
    siftUp(heap, heap->size - 1);
}

int extract(Heap *heap)
{
	int data;

	if (isEmptyHeap(heap))
		return INF;
	data = heap->nodes[0].data;
    heap->indexes[data] = heap->size - 1;
    heap->indexes[heap->nodes[heap->size - 1].data] = 0;
	heap->nodes[0] = heap->nodes[heap->size - 1];
    heap->size--;
    siftDown(heap, 0);
    return data;
}

void decreasePriority(Heap *heap, int priority, int data)
{
	int i = heap->indexes[data];
	if (heap->nodes[i].priority <= priority)
		return;
	heap->nodes[i].priority = priority;
	siftUp(heap, i);
}

int inHeap(Heap *heap, int data)
{
   return (heap->indexes[data] < heap->size);
}

int parent(int i)
{
	return (i - 1) / 2;
}

int left(int i)
{
	return 2 * i + 1;
}

int right(int i)
{
	return 2 * i + 2;
}

void siftUp(Heap *heap, int i)
{
	int p = parent(i);

    if (i > 0 && heap->nodes[p].priority > heap->nodes[i].priority) {
    	swap(&heap->indexes[heap->nodes[p].data],
				&heap->indexes[heap->nodes[i].data], sizeof(int));
    	swap(&heap->nodes[p], &heap->nodes[i], sizeof(HeapNode));
        siftUp(heap, p);
    }
}

void siftDown(Heap *heap, int i)
{
	int l = left(i);
	int r = right(i);
    int s = i;

    if (l < heap->size && heap->nodes[l].priority < heap->nodes[s].priority)
        s = l;
    if (r < heap->size && heap->nodes[r].priority < heap->nodes[s].priority)
        s = r;
    if (s != i) {
		swap(&heap->indexes[heap->nodes[s].data],
				&heap->indexes[heap->nodes[i].data], sizeof(int));
        swap(&heap->nodes[s], &heap->nodes[i], sizeof(HeapNode));
        siftDown(heap, s);
    }
}
