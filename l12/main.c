#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int hashFunction(char *word, int size) {
    int hash = 0;
    for (int i = 0; i < strlen(word); i++)
        hash = ((hash * 17) % size + word[i] % size) % size;
    return hash % size;
}

int main()
{
    FILE *fa = fopen("a.in", "r");
    FILE *fb = fopen("b.in", "r");

    HashTable *hashTableA = createHashTable(20, hashFunction);
    HashTable *hashTableB = createHashTable(20, hashFunction);

    char word[256];
    while (fscanf(fa, "%s", word) == 1)
        continue; /* citeste datele si numara aparitiile cuvintelor */
    while (fscanf(fb, "%s", word) == 1)
        continue; /* citeste datele si numara aparitiile cuvintelor */

    delete(hashTableB, "om"); /* nu este in nicio lista, ar trebui sa fie ok */
    delete(hashTableB, "cuc");
    delete(hashTableB, "gasca");
    delete(hashTableB, "gasca");
    /* afiseaza tabelele de dispersie */

    /* gaseste cuvintele comune si afiseaza minimul aparitiilor */

    freeHashTable(hashTableA);
    freeHashTable(hashTableB);
    fclose(fa);
    fclose(fb);
    return 0;
}
