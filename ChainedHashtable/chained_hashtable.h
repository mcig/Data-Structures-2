#ifndef CHAINED_HASHTABLE_H_
#define CHAINED_HASHTABLE_H_
#include "linked_list_library.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct {
	int tableSize;
	int (*hashFunction)(void *);
	LINKED_LIST *Table;
} HASHTABLE_t[1], *HASHTABLE;

HASHTABLE hashtable_init(int size, int (*hashFunction)(void *)) {
	HASHTABLE ht = (HASHTABLE) malloc(sizeof(HASHTABLE_t));
	ht->tableSize = size;
	ht->hashFunction = hashFunction;
	ht->Table = (LINKED_LIST*) malloc(sizeof(LINKED_LIST) * ht->tableSize);
	int i;
	for (i = 0; i < size; i++) {
		ht->Table[i] = linked_list_init();
	}
	return ht;
}

void hashtable_free(HASHTABLE ht) {
	int i;
	for (i = 0; i < ht->tableSize; i++) {
		linked_list_free(ht->Table[i]);
	}
	free(ht->Table);
	free(ht);
}

int hashtable_put(HASHTABLE ht, void *data) {
	int index = ht->hashFunction(data);
	linked_list_append(ht->Table[index], data);
	return index;
}

void hashtable_print(HASHTABLE ht, void (*printer)(FILE*, void*)) {
	int i = 0;
	printf("HASHTABLE:\n");
	for (i = 0; i < ht->tableSize; i++) {
		printf("%d: | ",i);
		linked_list_fprint(ht->Table[i], stdout, printer);
		printf(" |\n");
	}
}

#endif /* CHAINED_HASHTABLE_H_ */
