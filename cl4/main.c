#ifdef __STDC_ALLOC_LIB__
#define __STDC_WANT_LIB_EXT2__ 1
#else
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#define sd_assert(message, test) \
	do { \
		if (!(test)) \
			return message; \
	} while (0)

#define sd_run_test(test) \
	do { \
		char *message = test(); \
		if (message) \
			return message; \
	} while (0)

void *createInteger(void *data)
{
	int *integer = malloc(sizeof(int));

	if (integer == NULL)
		return NULL;
	*integer = *((int *) data);
	return integer;
}

void destroyInteger(void *data)
{
	int *integer = data;

	free(integer);
}

int compareInteger(void *data1, void *data2)
{
	int *integer1 = data1;
	int *integer2 = data2;

	return *integer1 - *integer2;
}

void printInteger(void *data)
{
	int *integer = data;

	printf("%2d", *integer);
}

void *createString(void *data)
{
	char *string = strdup(data);

	if (string == NULL)
		return NULL;
	return string;
}

void destroyString(void *data)
{
	char *string = data;

	free(string);
}

int compareString(void *data1, void *data2)
{
	char *string1 = data1;
	char *string2 = data2;

	return strcmp(string1, string2);
}

void printString(void *data)
{
	char *string = data;

	printf("%s", string);
}

char *test_init()
{
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	sd_assert("init 0", list != NULL);
	sd_assert("init 1", list->nill != NULL);
	sd_assert("init 2", list->nill->data == NULL);
	sd_assert("init 3", list->nill->next == list->nill);
	sd_assert("init 4", list->nill->prev == list->nill);
	sd_assert("init 5", list->head == list->nill);
	sd_assert("init 6", list->head == list->tail);
	sd_assert("init 7", list->createData == createInteger);
	sd_assert("init 8", list->destroyData == destroyInteger);
	sd_assert("init 9", list->compare == compareInteger);
	sd_assert("init 9", list->print == printInteger);
	destroyList(list);
	return NULL;
}

char *test_insert0()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = 0; i < n; i++)
		if (v[i] != 0)
			insert(list, v + i);
	{
		ListNode *node;
		int j;

		i = 5;
		insert(list, v + i);
		for (node = list->head, j = 0;
			node != list->nill && j < n;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert0 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = n - 1;
			node != list->nill && j >= 0;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert0 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_insert1()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = 0; i < n; i++) {
		ListNode *node;
		int j;

		insert(list, v + i);
		for (node = list->head, j = 0;
			node != list->nill && j < n;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert1 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = i;
			node != list->nill && j >= 0;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert1 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_insert2()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = n - 1; i >= 0; i--) {
		ListNode *node;
		int j;

		insert(list, v + i);
		for (node = list->head, j = i;
			node != list->nill && j < n;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert2 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = n - 1;
			node != list->nill && j >= i;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "insert2 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_delete0()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = 0; i < n; i++)
		insert(list, v + i);
	{
		ListNode *node;
		int j;

		i = 5;
		delete(list, v + i);
		for (node = list->head, j = 0;
			node != list->nill && j < n;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			if (j == 5)
				j++;
			sprintf(message, "delete0 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = n - 1;
			node != list->nill && j >= 0;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			if (j == 5)
				j--;
			sprintf(message, "delete0 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_delete1()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = 0; i < n; i++)
		insert(list, v + i);
	for (i = 0; i < n; i++) {
		ListNode *node;
		int j;

		delete(list, v + i);
		for (node = list->head, j = i + 1;
			node != list->nill && j < n;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "delete1 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = n - 1;
			node != list->nill && j > i;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "delete1 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_delete2()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = n - 1; i >= 0; i--)
		insert(list, v + i);

	for (i = n - 1; i >= 0; i--) {
		ListNode *node;
		int j;

		delete(list, v + i);
		for (node = list->head, j = 0;
			node != list->nill && j < i;
			node = node->next, j++) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "delete2 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
		for (node = list->tail, j = i - 1;
			node != list->nill && j >= 0;
			node = node->prev, j--) {
			char *message = calloc(100, sizeof(char));

			sprintf(message, "delete2 %d %d != %d",
					v[i], *((int *) node->data), v[j]);
			sd_assert(message, *((int *) node->data) == v[j]);
			free(message);
		}
	}
	destroyList(list);
	return NULL;
}

char *test_search()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = n - 1; i >= 0; i--)
		insert(list, v + i);
	for (i = 0; i < n; i++) {
		char *message = calloc(100, sizeof(char));
		ListNode *node = search(list, v + i);

		sprintf(message, "search %d != %d",
				v[i], *((int *) node->data));
		sd_assert(message, *((int *) node->data) == v[i]);
		free(message);
	}
	delete(list, v + 5);
	{
		ListNode *node = search(list, v + 5);

		sd_assert("search 0 is deleted", node == list->nill);
	}
	destroyList(list);
	return NULL;
}

char *test_print()
{
	int v[] = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5};
	int n = sizeof(v) / sizeof(v[0]);
	List *list = createList(createInteger, destroyInteger,
				compareInteger, printInteger);
	int i;

	for (i = n - 1; i >= 0; i--)
		insert(list, v + i);
	printOrder(list);
	printReverse(list);
	destroyList(list);
	return NULL;
}

char *test_strings()
{
	char *strings[] = {"anamaria", "ana", "maria",
				"genoveva", "nastasia", "andreea",
				"victoria", "ilinca", "tanta", "marcela",
				"oana", "georgiana", "ioana", "alexandra",
				"mariana", "virginia", "delia", "nicoleta"};
	int n = sizeof(strings) / sizeof(strings[0]);
	List *list = createList(createString, destroyString,
				compareString, printString);
	ListNode *start, *end, *node;
	int i;

	for (i = 0; i < n; i++)
		insert(list, strings[i]);
	delete(list, strings[9]);
	delete(list, strings[10]);
	delete(list, strings[11]);
	delete(list, strings[12]);
	delete(list, strings[13]);
	delete(list, strings[14]);
	delete(list, strings[15]);
	start = search(list, strings[5]);
	end = search(list, strings[4]);
	printf("Expected: %s\n",
		"andreea delia genoveva ilinca maria nastasia");
	printf("Resulted: ");
	for (node = start; node != end->next; node = node->next) {
		list->print(node->data);
		printf(" ");
	}
	printf("\n");
	destroyList(list);
	return NULL;
}

static char *all_tests()
{
	sd_run_test(test_init);
	sd_run_test(test_insert0);
	sd_run_test(test_insert1);
	sd_run_test(test_insert2);
	sd_run_test(test_delete0);
	sd_run_test(test_delete1);
	sd_run_test(test_delete2);
	sd_run_test(test_search);
	sd_run_test(test_print);
	sd_run_test(test_strings);
	return NULL;
}

int main(void)
{
	char *result = all_tests();

	if (result != NULL)
		printf("%s\n", result);
	else
		printf("Toate testele au trecut! Felicitari!\n");
	return result != NULL;
}
