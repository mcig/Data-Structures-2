/*
 * mustafa-cig-gokpinar-lab-2.c
 *
 *  Created on: 16 Eki 2020
 *      Author: Mustafa Çýð Gökpýnar
 */

/*lab2 linked_tree - linked_list search comparison*/
#include<time.h>
#include<stdio.h>
#include<stdlib.h>

int tree_ctr = 0;
int list_ctr = 0;

typedef struct LINKED_LIST_NODE_s *LINKED_LIST_NODE;
typedef struct LINKED_LIST_NODE_s {
	LINKED_LIST_NODE next;
	int key;
} LINKED_LIST_NODE_t[1];

typedef struct {
	LINKED_LIST_NODE head;
} LINKED_LIST_t[1], *LINKED_LIST;

LINKED_LIST linked_list_init() {
	LINKED_LIST t = (LINKED_LIST) malloc(sizeof(LINKED_LIST_t));
	t->head = NULL;
	return t;
}

void linked_list_free(LINKED_LIST list) {
	free(list);
}

void linked_list_append(LINKED_LIST list, int key) {
	LINKED_LIST_NODE node = (LINKED_LIST_NODE) malloc(
			sizeof(LINKED_LIST_NODE_t));
	LINKED_LIST_NODE temp = list->head;
	node->key = key;
	node->next = NULL;
	if (list->head == NULL) {
		list->head = node;
	} else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = node;
	}
}

void linked_list_search(LINKED_LIST list, int key) {
	LINKED_LIST_NODE node = list->head;
	int flag = 1;
	while (flag != -1) {
		if (node->key == key) {
			flag = -1;
		} else {
			node = node->next;
			list_ctr++;
		}
	}
}

typedef struct LINKED_TREE_NODE_s *LINKED_TREE_NODE;
typedef struct LINKED_TREE_NODE_s {
	LINKED_TREE_NODE left;
	LINKED_TREE_NODE right;
	int key;
	void *data;
} LINKED_TREE_NODE_t[1];

typedef struct {
	LINKED_TREE_NODE root;
} LINKED_TREE_t[1], *LINKED_TREE;

LINKED_TREE linked_tree_init() {
	LINKED_TREE t = (LINKED_TREE) malloc(sizeof(LINKED_TREE_t));
	t->root = NULL;
	return t;
}

void linked_tree_kill(LINKED_TREE t) {
	free(t);
}

LINKED_TREE_NODE linked_tree_node_init(int key, void *data) {
	LINKED_TREE_NODE n = (LINKED_TREE_NODE) malloc(sizeof(LINKED_TREE_NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->key = key;
	n->data = data;
	return n;
}

void linked_tree_node_kill(LINKED_TREE_NODE n) {
	free(n);
}

void linked_tree_insert(LINKED_TREE tree, int key, void *data) {
	LINKED_TREE_NODE curr;
	if (tree->root == NULL) {
		tree->root = linked_tree_node_init(key, data);
	} else {
		curr = tree->root;
		while (1) {
			if (key < curr->key) {
				if (curr->left == NULL) {
					curr->left = linked_tree_node_init(key, data);
					break;
				} else {
					curr = curr->left;
				}
			} else if (key > curr->key) {
				if (curr->right == NULL) {
					curr->right = linked_tree_node_init(key, data);
					break;
				} else {
					curr = curr->right;
				}
			} else {
				printf("Error: duplicate node.\n");
			}
		}
	}
}

void linked_tree_search(LINKED_TREE tree, int key) {
	LINKED_TREE_NODE curr = tree->root;
	while (curr != NULL) {
		tree_ctr++;
		int crnt_key = curr->key;

		if (key == crnt_key) {
			break;
		} else if (key > crnt_key) {
			curr = curr->right;
		} else {
			curr = curr->left;
		}
	}
}

int output_distinct_number(int *arr, int crnt_size, int upperLim) { //makes sure that we always generate distinct values
	int i = 0, rand_num = rand() % upperLim;
	while (i < crnt_size) {
		if (arr[i] == rand_num) {
			rand_num = rand() % upperLim;
			i = 0;
		} else {
			i++;
		}
	}
	arr[i] = rand_num;
	return rand_num;
}

int fill_structures_with_random(LINKED_LIST l, LINKED_TREE t, int size,
		int upperLim) {
	int i, *distinct_arr = malloc(sizeof(int) * size);
	int key; //this will be returned so we can search for it
	for (i = 0; i < size; i++) {
		int rand_num = output_distinct_number(distinct_arr, i, upperLim);
		linked_list_append(l, rand_num);
		linked_tree_insert(t, rand_num, NULL);
	}
	key = distinct_arr[(rand() % size)];
	free(distinct_arr);
	return key;
}

int main() {
	srand(time(NULL)); //randomly seeds the rand generator

	//WARNING!!! - THE SIZE MUST BE SMALLER THAN MAX RAND
	//UNLESS IT IS IMPOSSIBLE TO GENERATE DISTINCT VALUES
	//AND WE WOULD FIND OURSELVES IN AN NEVERENDING LOOP
	//SEE output_distinct_number() function for details

	int size = 10000;
	int maxRand = size * 10; //upper Limit for random number generator
	int key; //the key will be returned from the distinctly filled numbers array

	LINKED_LIST l = linked_list_init();
	LINKED_TREE t = linked_tree_init();

	key = fill_structures_with_random(l, t, size, maxRand);

	linked_list_search(l, key);

	linked_tree_search(t, key);

	printf(
			"I searched for key %d\nIn linked lists it took: %d steps\nIn binary search tree it took: %d steps\n",
			key, list_ctr, tree_ctr);
	linked_list_free(l);
	linked_tree_kill(t);
	return 0;
}

