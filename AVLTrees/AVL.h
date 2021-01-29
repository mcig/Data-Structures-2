#ifndef AVL_H_
#define AVL_H_
typedef struct AVL_NODE_s *AVL_NODE;
typedef struct AVL_NODE_s {
	AVL_NODE right;
	AVL_NODE left;
	int height;
	unsigned long key;
	void *data;
} AVL_NODE_t[1];

typedef struct {
	AVL_NODE root;
} AVL_TREE_t[1], *AVL_TREE;

AVL_TREE avl_tree_init() {
	AVL_TREE t = malloc(sizeof(AVL_TREE_t));
	t->root = NULL;
	return t;
}

AVL_NODE avl_node_init(unsigned long key, void *data) {
	AVL_NODE n = (AVL_NODE) malloc(sizeof(AVL_NODE_t));
	n->left = NULL;
	n->right = NULL;
	n->height = 0;
	n->key = key;
	n->data = data;
	return n;
}

void avl_tree_print(AVL_NODE node, int k) {
	int i;
	if (node != NULL) {
		avl_tree_print(node->right, k + 3);
		if (k == 0)
			printf("t->:");
		else
			printf("    ");
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		printf("%lu\n", node->key);
		fflush(stdout);
		avl_tree_print(node->left, k + 3);
	}
}

int max(int a, int b) {
	return a > b ? a : b;
}

int calculate_height(AVL_NODE node) {
	return node == NULL ? 0 : node->height;
}

int calculate_balance(AVL_NODE node) {
	return node == NULL ?
			0 : calculate_height(node->left) - calculate_height(node->right);
}

AVL_NODE avl_left_rotation(AVL_NODE p) {
	AVL_NODE c = p->right;

	p->right = c->left;
	c->left = p;

	p->height = max(calculate_height(p->left), calculate_height(p->right)) + 1;
	c->height = max(calculate_height(c->left), calculate_height(c->right)) + 1;
	return c;
}

AVL_NODE avl_right_rotation(AVL_NODE p) {
	AVL_NODE c = p->left;

	p->left = c->right;
	c->right = p;

	p->height = max(calculate_height(p->left), calculate_height(p->right)) + 1;
	c->height = max(calculate_height(c->left), calculate_height(c->right)) + 1;
	return c;
}

AVL_NODE avl_tree_insert_recursive(AVL_NODE node, unsigned long key, void *data) {
	if (node != NULL) {
		if (key < node->key) {
			node->left = avl_tree_insert_recursive(node->left, key, data);
		} else if (key > node->key) {
			node->right = avl_tree_insert_recursive(node->right, key, data);
		} else {
			printf("Error: duplicate node %lu.\n", key);
		}
	} else {
		node = avl_node_init(key, data);
	}

	//UPDATE Node's height using max
	node->height = max(calculate_height(node->left),
			calculate_height(node->right)) + 1;

	//CHECK BALANCE
	int bal = calculate_balance(node);

	//IF BALANCE IS BAD DO ROTATIONS

	if (bal < -1) { //First step right

		if (key < node->right->key) { //Right Left
			node->right = avl_right_rotation(node->right); //do right rot then left rot
			node = avl_left_rotation(node);
		}

		else { //Right Right
			node = avl_left_rotation(node);
		}

	} else if (bal > 1) { //First step left

		if (key > node->left->key) { //Left Right
			node->left = avl_left_rotation(node->left); //do left rot
			node = avl_right_rotation(node);
		} else { //Left Left
			node = avl_right_rotation(node); //do right rot
		}
	}

	return node;
}

void avl_tree_insert(AVL_TREE tree, unsigned long key, void *data) {
	if (tree->root == NULL) {
		tree->root = avl_node_init(key, data);
	} else {
		tree->root = avl_tree_insert_recursive(tree->root, key, data);
	}
}

AVL_NODE avl_tree_search(AVL_NODE currNode, unsigned long key) {
	if (currNode == NULL)
		return NULL;
	else if (currNode->key == key)
		return currNode;
	else if (key < currNode->key) {
		return avl_tree_search(currNode->left, key);
	} else {
		return avl_tree_search(currNode->right, key);
	}
}

void free_avl_tree(AVL_NODE node) {
	if (node == NULL)
		return;
	free_avl_tree(node->left);
	free_avl_tree(node->right);
	if (node->data != NULL)
		free(node->data);
	free(node);
}

#endif /* AVL_H_ */
