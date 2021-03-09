#include "hashtable.h"

HashTable *createHashTable(int size, int (*hashFunction)(char *key, int size))
{
    HashTable *table = malloc(sizeof(HashTable));
    table->entries = calloc(size, sizeof(HashEntry *));
    table->size = size;
    table->hashFunction = hashFunction;
    return table;
}

HashEntry *createHashEntry(char *key, int value)
{
    HashEntry *entry = malloc(sizeof(HashEntry));
    entry->key = calloc(strlen(key) + 1, sizeof(char));
    strcpy(entry->key, key);
    entry->value = value;
    entry->next = NULL;
    return entry;
}

int isEmpty(HashTable *table)
{
    for (int hash = 0; hash < table->size; hash++)
        if (table->entries[hash] != NULL)
            return 0;
    return 1;
}

void freeHashEntry(HashEntry *entry)
{
    free(entry->key);
    free(entry);
}

void freeHashTable(HashTable *table)
{
    for (int hash = 0; hash < table->size; hash++) {
        if (table->entries[hash] == NULL)
            continue;
        for (HashEntry *entry = table->entries[hash], *tmp = entry->next;
                entry != NULL; entry = tmp, tmp = entry->next) {
            freeHashEntry(entry);
            if (tmp == NULL)
                break;
        }
        table->entries[hash] = NULL;
    }
    free(table->entries);
    free(table);
}

int containsKey(HashTable *table, char *key)
{
	int hash = table->hashFunction(key, table->size);
	for (HashEntry *entry = table->entries[hash]; entry != NULL; entry = entry->next)
	{
		if (strcmp(entry->key, key) == 0)
			return 1;
	}
	return 0;
}

void put(HashTable *table, char *key, int value)
{
	int hash = table->hashFunction(key, table->size);
	if (!containsKey(table, key))
	{
		HashEntry *entry = createHashEntry(key, value);
		entry->next = table->entries[hash];
		table->entries[hash] = entry;
	}
}

HashEntry *get(HashTable *table, char *key)
{
	int hash = table->hashFunction (key, table->size);
	for (HashEntry *entry = table->entries[hash]; entry != NULL; entry = entry->next)
	{
		if (strcmp(entry->key, key) == 0)
			return entry;
	}
	return NULL;
}

int getOrDefault(HashTable *table, char *key, int value)
{
	HashEntry *entry = get(table, key);
	if (entry != NULL)
		return entry->value;
	return value;
}

void delete(HashTable *table, char *key)
{
}

void replace(HashTable *table, char *key, int value)
{
	HashEntry *entry = get(table, key);
	if (entry != NULL)
	{
		entry->value = value;
		return;
	}
	put(table, key, value);
}

void forEach(HashTable *table)
{
    for (int hash = 0; hash < table->size; hash++) {
        printf("[%d]: ", hash);
        for (HashEntry *entry = table->entries[hash]; entry != NULL;
                entry = entry->next)
            printf("(%s, %d) ", entry->key, entry->value);
        printf("\n");
    }
}