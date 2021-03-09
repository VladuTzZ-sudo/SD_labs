#ifndef __LIST_H__
#define __LIST_H__

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	void *data;
	struct node *next;
	struct node *prev;
} ListNode;

typedef struct List {
	ListNode *nill;
	ListNode *head;
	ListNode *tail;
	void *(*createData)(void *data);
	void (*destroyData)(void *data);
	int (*compare)(void *data1, void *data2);
	void (*print)(void *data);
} List;

List *createList(void *createData(void *data),
			void destroyData(void *data),
			int compare(void *data1, void *data2),
			void print(void *data));

ListNode *createListNode(List *list, void *value);

void destroyListNode(List *list, ListNode *node);

void destroyList(List *list);

void insert(List *list, void *data);

void delete(List *list, void *data);

ListNode *search(List *list, void *data);

void printOrder(List *list);

void printReverse(List *list);

#endif /* __LIST_H__ */
