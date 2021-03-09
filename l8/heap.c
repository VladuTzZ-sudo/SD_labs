#include "heap.h"

PriorityQueue *makeQueue(int capacity) {
	PriorityQueue *h;
	h = (PriorityQueue *)malloc(sizeof(PriorityQueue));
	h->capacity = capacity;
	h->size = 0;
	h->elem = (ItemType *)malloc(capacity*sizeof(ItemType));
	return h;
}

int getLeftChild(int i) {
	return 2*i;
}

int getRightChild(int i) {
	return 2*i+1;
}

int getParent(int i) {
	return i/2;
}

void siftUp(PriorityQueue *h, int idx) {
	int i;
	ItemType t;
	i = h->size;
	while ( i > 1 && h->elem[getParent(i)].prior > idx ) {
		t = h->elem[getParent(i)];
		h->elem[getParent(i)] = h->elem[i];
		h->elem[i]=t;
		i = i/2;	
	}
}

void insert(PriorityQueue *h, ItemType x) {
	if ( h->size + 1 == h->capacity ) {
		h->capacity = h->capacity *2;
		h->elem = (ItemType *)realloc(h->elem,h->capacity*sizeof(ItemType));
	} else {
		h->size++;
		h->elem[h->size] = x;
		if ( h->size > 1 ) {
			siftUp(h,h->elem[h->size].prior);
		}
	}
}

ItemType getMin(PriorityQueue *h) {
	return h->elem[1];
}

void siftDown(PriorityQueue *h, int idx) {
	int i;
	ItemType t;
        i = 1;
        while ( i < h->size && ( h->elem[getLeftChild(i)].prior < idx 
	|| h->elem[getRightChild(i)].prior < idx )) {
		if ( h->elem[getLeftChild(i)].prior < h->elem[getRightChild(i)].prior ) {
                	t = h->elem[getLeftChild(i)];
                	h->elem[getLeftChild(i)] = h->elem[i];
                	h->elem[i]=t;
                	i = 2*i;
		} else {
			t = h->elem[getRightChild(i)];
                        h->elem[getRightChild(i)] = h->elem[i];
                        h->elem[i]=t;
                        i = 2*i+1;
		}
        }	
}

ItemType removeMin(PriorityQueue *h) {
		ItemType y;
	y = getMin(h);
	h->elem[1] = h->elem[h->size];

	h->size--;
	siftDown(h,h->elem[1].prior);
	return y; /* just for compilation, bad practice */
}
