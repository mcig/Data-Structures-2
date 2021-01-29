#ifndef AUXILIARIES_H_
#define AUXILIARIES_H_

#include <stdio.h>
#include <stdlib.h>

#define uint64_t unsigned long
#define uint32_t unsigned int

uint64_t cycles_now(void) {
#if defined(__GNUC__)
	uint32_t lo, hi;
	__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
	return ((uint64_t) lo | ((uint64_t) hi << 32));
#else
 return 0;
 #endif
}

int my_pow(int base, int power) {
	int i, result = 1;
	for (i = 0; i < power; i++)
		result *= base;
	return result;
}

unsigned long* fill_arr_with_keys(int size) {
	int i;
	unsigned long *keys = malloc(sizeof(unsigned long) * size);
	if (keys == NULL) {
		printf("COULDN'T ALLOCATE ENOUGH MEMORY");
		return NULL;
	}

	for (i = 0; i < size; i++) {
		keys[i] = (unsigned long) rand() * (unsigned long) rand();
	}
	return keys;
}

#endif /* AUXILIARIES_H_ */
