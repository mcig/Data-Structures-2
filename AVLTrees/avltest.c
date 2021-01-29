#include <stdio.h>
#include <stdlib.h>
#include "AVL.h"

int main(int argc, char **argv) {
	AVL_TREE t = avl_tree_init();
	avl_tree_insert(t, 6, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 11, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 1, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 15, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 17, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 25, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 13, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 8, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 27, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");
	avl_tree_insert(t, 22, NULL);
	avl_tree_print(t->root, 0);
	printf("\n");


	free_avl_tree(t->root);
	free(t);
	return 0;
}
