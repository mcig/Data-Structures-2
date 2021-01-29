#include <stdio.h>
#include <stdlib.h>
#define MAX_COUNT 6
#define MIN_COUNT 4
#define PATH "btree.txt"

typedef struct B_NODE_s *B_NODE;
typedef struct B_NODE_s {
	int isLeaf;
	int size;
	int pos;
	unsigned long keys[MAX_COUNT];
	B_NODE children[MAX_COUNT + 1];
} B_NODE_t[1];

typedef struct {
	B_NODE root;
} B_TREE_t[1], *B_TREE;

B_TREE b_tree_init() {
	B_TREE bt;
	bt = malloc(sizeof(B_TREE_t));
	bt->root = NULL;
	return bt;
}

B_NODE b_node_init(unsigned long key, int isLeaf) {
	B_NODE node;
	node = malloc(sizeof(B_NODE_t));
	node->keys[0] = key;
	node->isLeaf = isLeaf;
	node->size = 1;
	return node;
}

void b_tree_free(B_NODE node) {
	int i;
	if (node->isLeaf == 1) {
		free(node);
	} else {
		for (i = 0; i <= node->size; i++) {
			b_tree_free(node->children[i]);
		}
	}
}

void disk_write(FILE *fp, B_NODE node) {
	fwrite(node, sizeof(B_NODE_t), 1, fp);
}
void disk_read(B_NODE node) {
	fread();
}
void b_tree_insert_nonfull(B_NODE node, unsigned long key, FILE *fp) {
	int i = node->size;
	if (node->isLeaf == 1) {
		while (i >= 1 && key < node->keys[i]) {
			node->keys[i + 1] = node->keys[i];
			i--;
		}
		node->keys[i + 1] = key;
		node->size++;
		disk_write(fp, node);
	} else {
		while (i >= 1 && key < node->keys[i]) {
			i--;
		}
		i++;

	}
}

void b_tree_insert(B_TREE bt, unsigned long key, FILE *fp) {
	B_NODE root = bt->root;
	if (root == NULL) {
		root = b_node_init(key, 1);
	} else {
		if (root->size == 2 * MIN_COUNT - 1) {
			B_NODE new = b_node_init(key, 0);
			new->children[0] = root;
			//split
		} else {
			b_tree_insert_nonfull(root, key);
		}
	}
}

int main() {
	FILE *fp = fopen(PATH, "wb+");

	fclose(fp);
}
