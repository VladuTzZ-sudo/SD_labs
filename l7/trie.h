#ifndef _TRIE_H
#define _TRIE_H

typedef struct trie_node trie_node;

typedef struct list_node {
    /* The character which links to this child */
    char letter;
    /* The pointer to the child */
    trie_node *child;

    /* The next element in the list */
    struct list_node *next;
} list_node;

struct trie_node {
    /* The number of occurrences for the word associated with the current node */
    int word_occurrences;
    /* A pointer to the head of the list of children */
    list_node *head;
};

// Creates the root trie_node and initializes it
trie_node* create_trie();

// Adds an occurrence to the word 'word' in the trie
void add_word(trie_node *trie, char *word);

// Returns the number of occurrences for the word 'word' in the trie
int search_word(trie_node *trie, char *word);

// Destroys the whole trie
void destroy_trie(trie_node *trie);

#endif
