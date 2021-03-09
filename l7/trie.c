#include "trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

trie_node* create_trie()
{
	list_node *list;
   
    	list = (list_node *)malloc(sizeof(list_node));

	list->child = NULL;
    	list->next = NULL;
    
    	trie_node *trie;

    	trie = (trie_node *)malloc(sizeof(trie_node));
    	trie->head = list;
    	return trie;
}

// Useful function: returns the trie_node associated with the letter 'letter'
// for the node 'node' or NULL if it doesn't exist
static trie_node* find_letter_node(trie_node *node, char letter)
{
	list_node *point;

	if (node->head != NULL)
		point = node->head;
	else
		return NULL;
	while (point != NULL){
		if (point->letter == letter) {
//			trie_node *trie;
						
//			trie = create_trie();
//			point->child = trie;
			
			return node;
		} else {
			if (point->child != NULL) {
				if (find_letter_node(node->head->child, letter) != NULL)
					return find_letter_node(node->head->child, letter);
			}
			point = point->next;
		}	
	}
	return NULL;
}

// Useful function: adds the letter 'letter' for the node 'node;
static trie_node* add_letter_node(trie_node *node, char letter)
{
    //TODO: Allocate new list node and set its fields
    //      (allocate a new trie_node for the child and set its fields aswell)

	list_node *point;

	point = (list_node *)malloc(sizeof(list_node));	
	point->letter = letter;
	point->next = NULL;

	trie_node *trie;

	trie = create_trie();
	
	point->child = trie;

    //TODO: Add the new node to the front of the initital node's list

	point->next = node->head;
	node->head = point;

    //TODO: Return the child trie_node
	return node->head->child;
}

// HINT: - could be a recursive function
//       - use the 'find_letter_node' and 'add_letter_node" functions
void add_word(trie_node *trie, char *word)
{	
	trie_node *node;
	int i,n;
	n = strlen(word);
	for (i = 0 ; i < n ; i++) {
		node = find_letter_node(trie, word[i]);	
		if (node == NULL) {
			node = add_letter_node(trie, word[i]);
			trie = node;
		} else {
			list_node *point;
			point = node->head;
			while (point->letter != word[i]) {
				point = point->next;
			}
			trie = point->child;
		}
		if ( i == n-1 ) {
			trie->word_occurrences++;	
		//	printf("%s %d\n", word, trie->word_occurrences);
		}
	}
	return;
}

int search_word(trie_node *trie, char *word)
{
	trie_node *node;
	int i,n;
	n = strlen(word);
	for ( i = 0 ; i <n ; i++ ) {
//		printf("%c\n", word[i]);
		node = find_letter_node(trie, word[i]);
		list_node *point;
		if ( node != NULL ){
		point = node->head;
	//	printf(" %c ", point->letter);
		while (point->letter != word[i]) {
			point = point->next;
		}
		trie = point->child;
		}
	}
	return trie->word_occurrences;	
}

// Useful function: destroys a linked list
// Should also call 'destroy_trie' for destroying the trie_node for the
// current list_node
static void destroy_list(list_node *trie)
{
	list_node *n;
	if ( trie != NULL ) {
		n = trie;
		while ( n->next ){
			if(n->next->next == NULL)
			{
				destroy_trie(n->child);
				list_node *nod;
			        nod = n->next;
				n->next = nod->next;
			//	destroy_trie(n->child);
				free(nod);
                         }
			n=n->next;
		}
	}
	free(n);	
}

// HINT: - call the 'destroy_list' function to destroy the list
void destroy_trie(trie_node *trie)
{
	destroy_list(trie->head);
	free(trie);
}
