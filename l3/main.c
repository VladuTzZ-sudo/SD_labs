#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main()
{
    List *list = createList();
    if (list == NULL) {
        printf("createList 1");
        return -1;
    }
    if (list->head != NULL || list->tail != NULL) {
        printf("createList 2");
        return -1;
    }
    if (!isEmpty(list)) {
        printf("isEmpty 1");
        return -1;
    }
    insert(list, 5);
    if (isEmpty(list)) {
        printf("isEmpty 2");
        return -1;
    }
    if (list->tail != list->head) {
        printf("insert 0");
        return -1;
    }
    insert(list, 3);
    insert(list, 2);
    insert(list, 4);
    insert(list, 1);
    if (list->head->data != 1) {
        printf("insert 1");
    }
    if (list->head->next->data != 2) {
        printf("insert 2");
    }
    if (list->head->next->next->data != 3) {
        printf("insert 3");
    }
    if (list->head->next->next->next->data != 4) {
        printf("insert 4");
    }
    if (list->head->next->next->next->next->data != 5) {
        printf("insert 5");
    }
    if (list->tail == list->head) {
        printf("insert 6");
        return -1;
    }
    delete(list, 1);
    if (list->head->data != 2) {
        printf("delete 1");
        return -1;
    }
    // printList(list);
    delete(list, 4);
    if (list->head->next->next->data != 5) {
        printf("delete 2");
        return -1;
    }
    // printList(list);
    delete(list, 2);
    if (list->head->data != 3) {
        printf("delete 3");
        return -1;
    }
    // printList(list);
    delete(list, 3);
    //printList(list);
    //printf("\n %d \n", list->head->data);
    if (list->head->data != 5) {
        printf("delete 4");
        return -1;
    }
    //printList(list);
    if (isEmpty(list)) {
        printf("isEmpty 3");
        return -1;
    }
    //printList(list);
    if (list->tail != list->head) {
        printf("insert 0");
        return -1;
    }
    //printList(list);
    if (list->tail->data != 5) {
        printf("delete 5");
        return -1;
    }
    //printf("%d %d\n", list->head->data,list->tail->data);
    delete(list, 5);
    //printList(list);
   // printf("nkniunibyub\n");
    if (!isEmpty(list)) {
        printf("isEmpty 4");
        return -1;
    }
    //printf("nkniunibyub\n");
    insert(list, 0);
    insert(list, 1);
    insert(list, 2);
    //printList(list);
    if (search(list, 0)->data != 0) {
        printf("search 0");
        return -1;
    }
    //printf("nkniunibyub\n");
    if (search(list, 1)->data != 1) {
        printf("search 1");
        return -1;
    }
//    printf("nkniunibyub\n");
//	printList(list);
    if (search(list, 2)->data != 2) {
        printf("search 2");
        return -1;
    }
 //   printf("nkniunibyub\n");

    if (search(list, 3) != NULL) {
        printf("search 3");
        return -1;
    }
    insert(list, 4);
    insert(list, 5);
    //printList(list);
    if (lengthIterative(list) != 5) {
        printf("length 1");
        return -1;
    }
    ///if (lengthStackRecursive(list) != 5) {
     //   printf("length 2");
     //   return -1;
   // }
    printList(list);
   // if (lengthTailRecursive(list) != 5) {
     //   printf("length 3");
       // return -1;
   // }//
   // printList(list);
    //printList(list);
    destroyListNodes(list);
    if (!isEmpty(list)) {
        printf("isEmpty 5");
        return -1;
    }
    //printf("nkniunibyub\n");

    destroyList(list);
    //printf("nkniunibyub\n");
    
    // TODO: run valgrind to check memory leaks
    list = createList();
    insert(list, 1);
    insert(list, 2);
    insert(list, 3);
    insert(list, 4);
    insert(list, 5);
    insert(list, 6);
    insert(list, 7);
    insert(list, 8);
    insert(list, 9);
    insert(list, 0);
    list->tail->next = search(list, 5);
    //printList(list);
    printf("%s\n", "Aici este loop de la functia detectLoop!" );
    if (!detectLoop(list)) {
        printf("detectLoop 1");
        return -1;
    }
    printf("nkniunibyub\n");
    detectAndRemoveLoop(list);
    if (list->tail->next != NULL) {
        printf("detectAndRemoveLoop 1");
        return -1;
    }
    return 0;
}
