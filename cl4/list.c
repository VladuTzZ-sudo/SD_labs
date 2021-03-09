#include "list.h"

List *createList(void *createData(void *), void destroyData(void *),
				 int compare(void *, void *), void print(void *))
{
	List *list = malloc(sizeof(List));
	ListNode *nill = malloc(sizeof(ListNode));

	if (list == NULL)
		return NULL;
	if (nill == NULL)
	{
		free(list);
		return NULL;
	}
	/* TODO: fill members */
	nill->data = NULL;
	list->nill = nill;
	list->head = nill;
	list->tail = nill;
	list->createData = createData;
	list->destroyData = destroyData;
	list->compare = compare;
	list->print = print;
	return list;
}

ListNode *createListNode(List *list, void *value)
{
	ListNode *node = malloc(sizeof(ListNode));

	if (node == NULL)
	{
		return NULL;
	}

	node->data = list->createData(value);
	node->next = list->nill;
	node->prev = list->nill;
	return node;
}

void destroyListNode(List *list, ListNode *node)
{
	list->destroyData(node->data);
	free(node);
}

void destroyList(List *list)
{
	ListNode *node = list->head;
	while (node != list->nill)
	{
		ListNode *tmp = node;
		node = node->next;
		destroyListNode(tmp);
	}
	destroyListNode(list->nill);
	free(list);
}

void insert(List *list, void *data)
{
	ListNode *newnod;
	newnod = createListNode(list, data);
	ListNode *nod = list->head;
	while (nod != list->nill && list->compare(nod->data, data) < 0)
	{
		nod = nod->next;
	}

	if (nod != list->nill && list->compare(nod->data, data) == 0)
	{
		destroyListNode(list, newnod);
		return;
	}

	newnod->next = nod;
	newnod->prev = nod->prev;

	if (list->head == nod)
	{
		list->head = newnod;
	}
	if (list->tail == nod->prev)
	{
		list->tail = newnod;
	}

	nod->prev->next = newnod;
	nod->prev = newnod;
}

void delete (List *list, void *data)
{
	ListNode *node = list->head;

	while (node != list->nill && list->compare(node->data, data) != 0)
		node = node->next;
	if (node == list->nill)
	{
		return;
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;
	if (list->head == node)
	{
		list->head = node->next;
	}
	if (list->tail == node)
	{
		list->tail = node->prev;
	}
	node->next->prev = node->prev;
	node->prev->next = node->next;

	//node->next=NULL;
	//node->prev=NULL;

	destroyListNode(list, node);
}

ListNode *search(List *list, void *data)
{
	ListNode *node = list->head;

	while (node != list->nill && list->compare(node->data, data) < 0)
	{
		node = node->next;
	}

	if (node != list->nill && list->compare(node->data, data) == 0)
	{
		return node;
	}
	return list->nill;
}

void printOrder(List *list)
{
	ListNode *node = list->head;

	for (node = list->head; node != list->nill; node = node->next)
	{
		list->print(node->data);
		printf(" ");
	}
	printf("\n");
}

void printReverse(List *list)
{
	ListNode *node = list->head;

	for (node = list->tail; node != list->nill; node = node->prev)
	{
		list->print(node->data);
		printf(" ");
	}
	printf("\n");
}
