#ifndef TREE_H_
#define TREE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct NODE_s *NODE;
typedef struct NODE_s {
	NODE left;
	NODE right;
	unsigned long key;
	void *data;
} NODE_t[1];

typedef struct {
	NODE root;
} TREE_t[1], *TREE;

TREE tree_init() {
	TREE t = (TREE) malloc(sizeof(TREE_t));
	t->root = NULL;
	return t;
}

NODE tree_node_init(unsigned long key, void *data) {
	NODE n = (NODE) malloc(sizeof(NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

void tree_kill(TREE t) {
	free(t);
}

void tree_node_kill(NODE n) {
	free(n);
}

void tree_kill_children(NODE node) {
	if (node != NULL) {
		tree_kill_children(node->left);
		tree_kill_children(node->right);
		free(node);
	}
}

void tree_print(NODE node, int k) {
	int i;
	if (node != NULL) {
		tree_print(node->right, k + 3);
		if (k == 0)
			printf("t->:");
		else
			printf("    ");
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		printf("%lu\n", node->key);
		fflush(stdout);
		tree_print(node->left, k + 3);
	}
}

void tree_traverse_inorder(NODE node) {
	if (node != NULL) {
		tree_traverse_inorder(node->left);
		printf("%lu %p %p %p \n", node->key, node, node->left, node->right);
		fflush(stdout);
		tree_traverse_inorder(node->right);
	}
}

NODE tree_insert_recursive(NODE node, unsigned long key, void *data) {
	if (node != NULL) {
		if (key < node->key) {
			node->left = tree_insert_recursive(node->left, key, data);
		} else if (key > node->key) {
			node->right = tree_insert_recursive(node->right, key, data);
		} else {
			printf("Error: duplicate node %lu.\n", key);
		}
	} else {
		node = tree_node_init(key, data);
	}
	return node;
}

void tree_insert(TREE tree, unsigned long key, void *data) {
	if (tree->root == NULL) {
		tree->root = tree_node_init(key, data);
	} else {
		tree->root = tree_insert_recursive(tree->root, key, data);
	}
}

void fill_arr_with_unique_randoms(int *arr, int count, int randomLimit) {
	if (count > randomLimit) {
		fprintf(stderr,
				"Function aborted as count > randomLimit will generate an infinite loop\n");
		return;
	}

	int i, randomNum, *checkTableForUniqueness = calloc(randomLimit,
			sizeof(int));
	for (i = 0; i < count; i++) {
		do {
			randomNum = 1 + rand() % (randomLimit - 1);
		} while (checkTableForUniqueness[randomNum] == 1);

		arr[i] = randomNum;
		checkTableForUniqueness[randomNum] = 1;
	}

	free(checkTableForUniqueness);
}

void fill_tree_keys_with_unique_random(TREE t, int count, int randomLimit) {
	int i = 0;
	int *arr = malloc(sizeof(int) * count);
	fill_arr_with_unique_randoms(arr, count, randomLimit);
	for (i = 0; i < count; ++i) {
		tree_insert(t, arr[i], NULL);
	}
	free(arr);
}

void fill_tree_keys_with_unique_random_v2(TREE t, int count, int randomLimit,
		int **keysArr) {
	int i = 0;
	int *arr = malloc(sizeof(int) * count);
	fill_arr_with_unique_randoms(arr, count, randomLimit);
	for (i = 0; i < count; ++i) {
		tree_insert(t, arr[i], NULL);
	}
	if (keysArr == NULL)
		free(arr);
	else {
		*keysArr = arr;
	}
}

void delete_function_tester(TREE t, int nodeCount, int *keysArr,
		void (*generic_delete_function)(TREE, unsigned long)) {
	int i;
	for (i = 0; i < nodeCount; i++) {
		printf("\n******************\nDeleted %d\n******************\n\n",
				keysArr[i]);
		generic_delete_function(t, keysArr[i]);
		tree_print(t->root, 0);
	}
}

void tree_delete_node_unbalanced_iterative(TREE tree, unsigned long key) {
	NODE parent, node; //left child right child
	int last;

	last = 0;
	parent = (NODE) tree;   // tree->root  ===  parent->left
	node = tree->root;
	while (node != NULL) {
		if (key < node->key) {
			parent = node;
			node = node->left;
			last = 0;
		} else if (key > node->key) {
			parent = node;
			node = node->right;
			last = 1;
		} else {
			break;
		}
	}
	if (node == NULL) {
		printf("The node does not exist!\n");
		return;
	}

	if (((node->left == NULL) && (node->right == NULL))   //No child
	|| ((node->left != NULL) && (node->right == NULL))) {  //OR Only Left Child
		if (last == 0) {
			parent->left = node->left;
		} else {
			parent->right = node->left;
		}
	} else {  //Two Children OR Only Right Child
		if ((node->left != NULL) && (node->right != NULL)) {  //Two Children
			//right based deletion
			NODE curr = node->right;
			while (curr->left != NULL) {
				curr = curr->left;
			}
			curr->left = node->left;
		}
		if (last == 0) {
			parent->left = node->right;
		} else {
			parent->right = node->right;
		}
	}
	free(node->data); // May have special data deletion!!!
	tree_node_kill(node);
}

void tree_delete_node_balanced_iterative(TREE tree, unsigned long key) {
	NODE parent, node; //left child right child
	int last;

	last = 0;
	parent = (NODE) tree;   // tree->root  ===  parent->left
	node = tree->root;
	while (node != NULL) {
		if (key < node->key) {
			parent = node;
			node = node->left;
			last = 0;
		} else if (key > node->key) {
			parent = node;
			node = node->right;
			last = 1;
		} else {
			break;
		}
	}
	if (node == NULL) {
		printf("The node does not exist!\n");
		return;
	}

	if (((node->left == NULL) && (node->right == NULL))
			|| ((node->left != NULL) && (node->right == NULL))) { //No child or Only Left Child.
		if (last == 0) {
			parent->left = node->left;
		} else {
			parent->right = node->left;
		}
	} else if ((node->left == NULL) && (node->right != NULL)) { //Right child.
		if (last == 0) {
			parent->left = node->right;
		} else {
			parent->right = node->right;
		}
	} else {                                                   // Two children.
		//right based
		NODE subparent = NULL, curr = node->right;
		while (curr->left != NULL) {
			subparent = curr;
			curr = curr->left;
		}

		void *swap = node->data;
		node->data = curr->data;
		curr->data = swap;
		node->key = curr->key;

		if (subparent == NULL) {
			node->right = curr->right;
		} else {
			subparent->left = curr->right;
		}

		node = curr;//Making node point to curr so that we don't have to write additional freeing code
		//we will just use the already written one (2 lines below)
	}
	free(node->data); // May have special data deletion!!!
	tree_node_kill(node);
}

NODE tree_delete_node_unbalanced_recursive_helper(NODE node, unsigned long key) {
	if (node == NULL) {
		return node;
	}

	if (node->key != key) {
		if (key < node->key) {
			node->left = tree_delete_node_unbalanced_recursive_helper(
					node->left, key);
		} else {
			node->right = tree_delete_node_unbalanced_recursive_helper(
					node->right, key);
		}
	} else {
		if (((node->left == NULL) && (node->right == NULL))   //No child
		|| ((node->left != NULL) && (node->right == NULL))) { //OR Only Left Child
			NODE left = node->left;
			free(node->data); // May have special data deletion!!!
			tree_node_kill(node);
			return left;
		} else {  //Two Children OR Only Right Child
			if ((node->left != NULL) && (node->right != NULL)) {  //Two Children
				//right based deletion
				NODE curr = node->right;
				while (curr->left != NULL) {
					curr = curr->left;
				}
				curr->left = node->left;
			}
			NODE right = node->right;
			free(node->data); // May have special data deletion!!!
			tree_node_kill(node);
			return right;
		}
	}
	return node;
}

void tree_delete_node_unbalanced_recursive(TREE t, unsigned long key) {
	t->root = tree_delete_node_unbalanced_recursive_helper(t->root, key);
}

NODE tree_delete_node_balanced_recursive_helper(NODE node, unsigned long key) {
	if (node == NULL) {
		return node;
	}

	if (node->key != key) {
		if (key < node->key) {
			node->left = tree_delete_node_balanced_recursive_helper(node->left,
					key);
		} else {
			node->right = tree_delete_node_balanced_recursive_helper(
					node->right, key);
		}
	} else {
		if (((node->left == NULL) && (node->right == NULL))   //No child
		|| ((node->left != NULL) && (node->right == NULL))) { //OR Only Left Child
			NODE left = node->left;
			free(node->data); // May have special data deletion!!!
			tree_node_kill(node);
			return left;
		} else if ((node->left == NULL) && (node->right != NULL)) { //Right child.
			NODE right = node->right;
			free(node->data); // May have special data deletion!!!
			tree_node_kill(node);
			return right;
		} else {                                                // Two children.
			//right based
			NODE curr = node->right;
			while (curr->left != NULL) {
				curr = curr->left;
			}

			free(node->data); // May have special data deletion!!!
			node->data = curr->data;
			node->key = curr->key;

			node->right = tree_delete_node_balanced_recursive_helper(
					node->right, curr->key); //killing the copied (duplicate) node
		}
	}
	return node;
}

void tree_delete_node_balanced_recursive(TREE t, unsigned long key) {
	t->root = tree_delete_node_balanced_recursive_helper(t->root, key);
}
#endif /* TREE_H_ */
