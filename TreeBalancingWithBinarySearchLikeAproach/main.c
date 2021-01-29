#include "tree.h"
#include <time.h>

void nodeArr_push(NODE *nodeArr, int nodeCount, NODE node) {
	int i, pushed = 0;
	for (i = 0; i < nodeCount && !pushed; i++) {
		if (nodeArr[i] == 0) {
			nodeArr[i] = node;
			pushed = 1;
		}
	}
}

int isNodeArrEmpty(NODE *nodeArr, int nodeCount) {
	int i, isEmpty = 1;
	for (i = 0; i < nodeCount && isEmpty == 1; i++) {
		if (nodeArr[i] != 0) {
			isEmpty = 0;
		}
	}
	return isEmpty;
}

void tree_inorder_arr_fill(NODE node, NODE *nodeArr, int nodeCount) {
	if (node != NULL) {
		tree_inorder_arr_fill(node->left, nodeArr, nodeCount);
		nodeArr_push(nodeArr, nodeCount, node);
		tree_inorder_arr_fill(node->right, nodeArr, nodeCount);
	}
}

NODE tree_balancer_recursive(NODE *nodeArr, int l) {
	int n = l / 2;
	if (l == 0)
		return NULL;
	nodeArr[n]->left = tree_balancer_recursive(&nodeArr[0], n);
	nodeArr[n]->right = tree_balancer_recursive(&nodeArr[n + 1], l - n - 1);
	return nodeArr[n];
}

void tree_balancer(TREE t, NODE *nodeArr, int nodeCount) {
	int mid = nodeCount / 2;
	tree_inorder_arr_fill(t->root, nodeArr, nodeCount);
	nodeArr[mid]->left = tree_balancer_recursive(&nodeArr[0], mid);
	nodeArr[mid]->right = tree_balancer_recursive(&nodeArr[mid + 1],
			nodeCount - mid - 1);
	t->root = nodeArr[mid];
}

int main(int argc, char **argv) {
	TREE t = tree_init();
	int i, *keysArr, nodeCount = 3;
	NODE *nodeArr = calloc(nodeCount, sizeof(NODE));
	srand(time(NULL));
	fill_tree_keys_with_unique_random_v2(t, nodeCount, nodeCount * 10,
			&keysArr);
	tree_print(t->root, 0);
	printf("\n******************\n");
	tree_balancer(t, nodeArr, nodeCount);
	tree_print(t->root, 0);
	for (i = 0; i < nodeCount; i++) {
		tree_delete_node_balanced_iterative(t, keysArr[i]);
	}
	tree_print(t->root, 3);
	free(keysArr);
	free(nodeArr);
	tree_kill(t);
	return 0;
}
