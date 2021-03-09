#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
    char *key;
    int value;
    struct entry *next;
} HashEntry;

typedef struct table {
    HashEntry **entries;
    int size;
    int (*hashFunction)(char *key, int size);
} HashTable;

HashTable *createHashTable(int size, int (*hashFunction)(char *key, int size));

HashEntry *createHashEntry(char *key, int value);

int isEmpty(HashTable *hashTable);

void freeHashEntry(HashEntry *hashEntry);

void freeHashTable(HashTable *hashTable);

int containsKey(HashTable *hashTable, char *key);

void put(HashTable *hashTable, char *key, int value);

HashEntry *get(HashTable *hashTable, char *key);

int getOrDefault(HashTable *hashTable, char *key, int value);

void delete(HashTable *table, char *key);

void replace(HashTable *hashTable, char *key, int value);

void forEach(HashTable *hashTable);

#endif // HASHTABLE_H_INCLUDED
