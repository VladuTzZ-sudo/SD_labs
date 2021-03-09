// Sorted Singly Linked List

#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef struct node{
	int data;
	struct node *next;
} ListNode;

typedef struct List{
	ListNode *head;
	ListNode *tail;
} List;

List *createList();

ListNode *createListNode(int data);

void destroyListNode(ListNode *node);

void destroyListNodes(List *node);

void destroyList(List *list);

int isEmpty(List *list);

void insert(List *list, int data);

void delete(List *list, int data);

ListNode *search(List *list, int data);

int lengthIterative(List *list);

int lengthStackRecursive(List *list);

int lengthTailRecursive(List *list);

void printList(List *list);

int detectLoop(List *list);

void detectAndRemoveLoop(List *list);

#endif // LIST_H_INCLUDED
