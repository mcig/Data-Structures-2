#include <stdio.h>
#include <time.h>
#include "RedBlackTree.h"
#include "AVL.h"
#include "auxiliaries.h"

int main() {
	srand(time(NULL));
	int currPower = 5;
	int size;
	AVL_TREE avl_t = avl_tree_init();
	RED_BLACK_TREE rb_t = red_black_tree_init();
	uint64_t st, fn;

	while (currPower < 26) { //all test cases
		size = my_pow(2, currPower);
		//filling the array
		unsigned long *keys = fill_arr_with_keys(size);
		if (keys == NULL)
			return 0;

		//INSERTS
		int i;
		//testing AVL insert
		st = cycles_now();

		for (i = 0; i < size; i++) {
			avl_tree_insert(avl_t, keys[i], NULL);
		}

		fn = cycles_now();
		printf("AVL Insert with 2^%d keys took %lu clock cycles to execute.\n",
				currPower, (fn - st));

		//testing RB insert
		st = cycles_now();

		for (i = 0; i < size; i++) {
			red_black_tree_insert(rb_t, keys[i], NULL);
		}

		fn = cycles_now();
		printf("RB  Insert with 2^%d keys took %lu clock cycles to execute.\n",
				currPower, (fn - st));

		printf("\n");
		//SEARCHES
		unsigned long searchKey = keys[rand() % size]; //choosing a random key from the array
		//testing AVL Search
		st = cycles_now();

		if (avl_tree_search(avl_t->root, searchKey) == NULL)
			printf("Key %lu couldn't found in AVL tree", searchKey);

		fn = cycles_now();
		printf(
				"AVL Search for key: %lu on 2^%d keys took %lu clock cycles to execute.\n",
				searchKey, currPower, (fn - st));

		//testing RB Search
		st = cycles_now();

		if (rb_tree_search(rb_t->root, searchKey) == NULL)
			printf("Key %lu couldn't found in AVL tree", searchKey);

		fn = cycles_now();
		printf(
				"RB  Search for key: %lu on 2^%d keys took %lu clock cycles to execute.\n",
				searchKey, currPower, (fn - st));

		printf(
				"\n***************************************************************************\n");
		currPower++;
		//FREE TREE NODES AND ARRAY
		free_avl_tree(avl_t->root);
		free_rb_tree(rb_t->root);
		avl_t->root = NULL;
		rb_t->root = NULL;
		free(keys);
	}
	//FREE TREES
	free(avl_t);
	free(rb_t);
	return 0;
}
