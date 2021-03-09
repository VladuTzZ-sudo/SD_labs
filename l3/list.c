#include "list.h"

List *createList()
{
    List *list;
    list = (List*)malloc(sizeof(List));
    list->head=NULL;
    list->tail=NULL;
    return list;
}

ListNode *createListNode(int data)
{
    ListNode *nod;
    nod = (ListNode*)malloc(sizeof(ListNode));
    nod->data = data;
    nod->next=NULL;
    return nod;
}

void destroyListNode(ListNode *node)
{
    node->next=NULL;
    free(node);
    return;
}

void destroyListNodes(List *list)
{
    ListNode *nod1,*nod2;
    nod1=list->head;
    if ( nod1 != list->tail ){
    nod2=nod1->next;
    while ( nod1->next != NULL ){
    	nod2 = nod1;
	nod1 = nod1->next;
	destroyListNode(nod2);
    }
    destroyListNode(nod1);
    list->head=NULL;
    list->tail=NULL;
    }
    else{
    destroyListNode(nod1);
    list->head=NULL;
    list->tail=NULL;
    }
    return;
}

void destroyList(List *list)
{
      if ( list->head == NULL ){
      	free(list);
      }
      else{
      destroyListNodes(list);
    //  free(list->head);
  //    free(list->tail);
      free(list);
      }
      return;
}

int isEmpty(List *list)
{
    if ( list->head == NULL ){
    	return 1;
    }
    return 0;
}

void insert(List *list, int data)
{
    ListNode *p,*q,*nou;
    nou=createListNode(data);
    if ( list->head==NULL || data < list->head->data ){
    	nou->next=list->head;
	list->head=nou;
	if ( nou->next == NULL ){
	list->tail=nou;
	}
    }
    else{
    	p = list->head;
	q = list->head;
	while(p!=NULL && p->data < data){
		q=p;
		p=p->next;
	}
	if ( p == NULL ){
		list->tail=nou;
	}
	nou->next=p;
	q->next=nou;
    }
}

void delete(List *list, int data)
{
    ListNode *nod1,*nod2;
    nod1 = search(list,data);
    nod2 = list->head;
    if ( nod2 == nod1 ){
	if ( nod1->next != NULL){
	list->head=nod1->next;
	}
	else{
	list->head=NULL;
	}
	destroyListNode(nod1);
	if ( list->head == NULL ){
		list->tail=NULL;
	}
    }
    else{
    	while ( nod2->next != nod1 ){
    		nod2=nod2->next;
	}
    nod2->next=nod1->next;
    if ( nod1->next == NULL){
    	list->tail=nod2;
    }
    destroyListNode(nod1);
    return;
    }
}

ListNode *search(List *list, int data)
{
    ListNode *nod1;
    nod1=list->head;
    do{
    	if ( nod1->data == data ){
		return nod1;
	}
	else{
		nod1=nod1->next;
	}
    }while( nod1 != NULL);
    return NULL;
}

int lengthIterative(List *list)
{
    ListNode *nod1;
    nod1=list->head;
    int contor;
    contor=1;
    while ( nod1 -> next != NULL ){
    	contor++;
	nod1=nod1->next;
    }
    return contor;
}

int lengthStackRecursive(List *list)
{
    return -1;
}

int lengthTailRecursive(List *list)
{
    ListNode *nod1,*nod2;
    nod1=list->head;
    nod2=list->tail;
    if ( nod1 != nod2 ){
    	nod1=nod1->next;
	return 1 + lengthTailRecursive(list);	
    }
    return 1;
}

void printList(List *list)
{
    ListNode *nod;
    nod = list->head;
    while ( nod -> next != NULL ){
    	printf("%d ", nod->data);
	nod = nod->next;
    }
    printf("%d\n", nod->data);
    return;
}

int detectLoop(List *list)
{
    ListNode *nod1,*nod2;
    nod1=list->head;
    nod2=list->head;
    int ok;
    ok = 0;
    while ( nod1 != NULL || ok ==0  ){
	nod2=list->head;
    	do{
		if ( nod1->next == nod2 ){
			ok=1;
		}
		nod2=nod2->next;
	}while ( nod2 != nod1 || nod2 != NULL );
	nod1=nod1->next;
    }
    if ( ok == 1 ){
    	return 1;
    }   
    // DO NOT USE TAIL MEMBER OF LIST
    return 0;
}

void detectAndRemoveLoop(List *list)
{
    ListNode *nod1,*nod2;
    nod1=list->head;
    nod2=list->head;
    while ( nod1->next != NULL ){
        while ( nod2->next != nod1 ){
                if ( nod1->next == nod2 ){
                        nod1->next=NULL;
                }
        }
        nod1=nod1->next;
    }
    // DO NOT USE TAIL MEMBER OF LIST
    return;
}
