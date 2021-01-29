#include <stdio.h>
#include <stdlib.h>
#include "chained_hashtable.h"
#define tableSize 10
int basicIntHasher(void *data) {
	return *(int*) data % tableSize;
}

int main(int argc, char **argv) {
	int arr[] = { 123, 25, 5329, 6767, 21, 6856, 123341, 48374, 89, 4 };
	HASHTABLE ht = hashtable_init(tableSize, basicIntHasher);
	int i=0;
	for(i=0;i<sizeof(arr)/sizeof(int);i++){
		hashtable_put(ht,&arr[i]);
	}
	hashtable_print(ht,integer_printer);
	hashtable_free(ht);
	return 0;
}

