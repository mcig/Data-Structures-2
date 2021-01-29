#include <stdio.h>
#include "RedBlackTree.h"

int main() {
	RED_BLACK_TREE t = red_black_tree_init();
	red_black_tree_insert(t, 42, NULL);
	red_black_tree_insert(t, 17, NULL);
	red_black_tree_insert(t, 22, NULL);
	red_black_tree_insert(t, 5, NULL);
	red_black_tree_insert(t, 2, NULL);
	red_black_tree_insert(t, 19, NULL);
	red_black_tree_insert(t, 18, NULL);
	red_black_tree_insert(t, 15, NULL);
	red_black_tree_insert(t, 4, NULL);
	red_black_tree_insert(t, 1, NULL);
	red_black_tree_insert(t, 0, NULL);
	red_black_tree_insert(t, 12, NULL);
	red_black_tree_insert(t, 13, NULL);
	red_black_tree_insert(t, 14, NULL);
	red_black_tree_insert(t, 16, NULL);
	red_black_tree_insert(t, 10, NULL);
	red_black_tree_insert(t, 11, NULL);
	red_black_tree_insert(t, 137, NULL);
	red_black_tree_insert(t, 100, NULL);
	red_black_tree_insert(t, 99, NULL);
	red_black_tree_insert(t, 89, NULL);
	red_black_tree_insert(t, 82, NULL);
	red_black_tree_insert(t, 77, NULL);
	red_black_tree_insert(t, 92, NULL);

	rb_tree_print_colorful(t->root, 0);
	printf("\n");
	free_rb_tree(t->root);
	free(t);
	return 0;
}

