/*
 * Mustafa_Cig_Gokpinar.c
 *
 *  Created on: 23 Eki 2020
 *      Author: Mustafa Çýð Gökpýnar
 */

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "tree.h"

//function prototypes
void levelByLevelTraverse(TREE);

int main() {
	TREE t = tree_init();
	int nodeCount = 10;
	fill_tree_keys_with_unique_random(t,nodeCount,nodeCount * 10);

	printf("Tree Using Tree Print:\n");
	tree_print(t->root,0);


	printf("\n\nTree Using Traverse Algorithm:\n");
	levelByLevelTraverse(t);


	tree_kill_children(t->root);
	tree_kill(t);
	return 0;
}


//function declarations
void levelByLevelTraverse(TREE tree) {
	NODE node = tree->root;

	if (node == NULL)
		return;

	LINKED_QUEUE Q = linked_queue_init();

	linked_queue_enqueue(Q, node);

	while (!linked_queue_is_empty(Q)) {
		node = linked_queue_dequeue(Q);
		printf("Visited Node With Key: %lu\n",node->key);
		if (node->left != NULL)
			linked_queue_enqueue(Q,node->left);
		if (node->right != NULL)
			linked_queue_enqueue(Q,node->right);
	}
	linked_queue_free(Q);
}
