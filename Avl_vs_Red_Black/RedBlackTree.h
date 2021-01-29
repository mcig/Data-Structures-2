#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

#include <stdio.h>
#include <stdlib.h>

//These are used in colorful tree print function to colorize the tree
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_RESET "\x1b[0m"

//I used enumeration instead of a single char to represent the color
//which in my opinion made functions a bit easier to read
enum Color {
	Red = 1, Black = 0
};

//struct defs
typedef struct RED_BLACK_NODE_s *RED_BLACK_NODE;
typedef struct RED_BLACK_NODE_s {
	RED_BLACK_NODE right;
	RED_BLACK_NODE left;
	unsigned long key;
	void *data;
	enum Color color;
} RED_BLACK_NODE_t[1];

typedef struct {
	RED_BLACK_NODE root;
} RED_BLACK_TREE_t[1], *RED_BLACK_TREE;

//initializing functions
RED_BLACK_NODE red_black_node_init(unsigned long key, void *data) {
	RED_BLACK_NODE node = malloc(sizeof(RED_BLACK_NODE_t));
	node->color = Red;
	node->key = key;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

RED_BLACK_TREE red_black_tree_init() {
	RED_BLACK_TREE t = malloc(sizeof(RED_BLACK_TREE_t));
	t->root = NULL;
	return t;
}

//helper function to handle null cases
enum Color get_color(RED_BLACK_NODE node) {
	return node == NULL ? Black : node->color;
}

void recolour(RED_BLACK_NODE node) {
	node->left->color = Black;
	node->right->color = Black;
	node->color = Red;
}

//rotations
RED_BLACK_NODE rb_left_rotation(RED_BLACK_NODE p) {
	RED_BLACK_NODE c = p->right;

	p->right = c->left;
	c->left = p;

	enum Color tmp = p->color;
	p->color = c->color;
	c->color = tmp;

	return c;
}

RED_BLACK_NODE rb_right_rotation(RED_BLACK_NODE p) {
	RED_BLACK_NODE c = p->left;

	p->left = c->right;
	c->right = p;

	enum Color tmp = p->color;
	p->color = c->color;
	c->color = tmp;

	return c;
}

RED_BLACK_NODE red_black_tree_insert_recursive(RED_BLACK_NODE node,
		unsigned long key, void *data) {
	int direction = 0;

	if (node != NULL) {
		if (key < node->key) {
			node->left = red_black_tree_insert_recursive(node->left, key, data);
		} else if (key > node->key) {
			direction = 1;
			node->right = red_black_tree_insert_recursive(node->right, key,
					data);
		} else {
			return node;
		}
	} else {
		node = red_black_node_init(key, data);
	}

	RED_BLACK_NODE uncle;
	RED_BLACK_NODE p;

	if (direction == 1) {
		uncle = node->left;
		p = node->right;
	} else {
		uncle = node->right;
		p = node->left;
	}

	//IS NODE GRANDPARENT CHECKS
	if (node->left == NULL && node->right == NULL) //we are not child
		return node;
	if (p->key == key) //we are not parent
		return node;
	if(p->color == Black) //No RR conflict case 1
		return node;
	//there isn't a RR conflict case 2
	if (p->color == Red && get_color(p->left) == Black
			&& get_color(p->right) == Black)
		return node;

	//CORRECTIONS
	if (get_color(uncle) == Red) {
		recolour(node);
	} else { //uncle is black
		if (direction == 0) {
			if (key > p->key) { //left right
				node->left = rb_left_rotation(node->left);
				node = rb_right_rotation(node);
			} else
				//left left
				node = rb_right_rotation(node);
		} else {
			if (key < p->key) { //right left
				node->right = rb_right_rotation(node->right);
				node = rb_left_rotation(node);
			} else
				//right right
				node = rb_left_rotation(node);
		}
	}

	return node;

}

void red_black_tree_insert(RED_BLACK_TREE tree, unsigned long key, void *data) {
	if (tree->root == NULL) {
		tree->root = red_black_node_init(key, data);
	} else {
		tree->root = red_black_tree_insert_recursive(tree->root, key, data);
	}
	tree->root->color = Black;
}

//search
RED_BLACK_NODE rb_tree_search(RED_BLACK_NODE currNode, unsigned long key) {
	if (currNode == NULL)
		return NULL;
	else if (currNode->key == key)
		return currNode;
	else if (key < currNode->key) {
		return rb_tree_search(currNode->left, key);
	} else {
		return rb_tree_search(currNode->right, key);
	}
}

//printers
//a colorful way to print the tree. In my computer this only works in powershell
void rb_tree_print_colorful(RED_BLACK_NODE node, int k) {
	int i;
	if (node != NULL) {
		rb_tree_print_colorful(node->right, k + 3);
		if (k == 0)
			printf("t->:");
		else
			printf("    ");
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		if (node->color == Red)
			printf(ANSI_COLOR_RED);
		printf("%lu\n", node->key);
		printf(ANSI_COLOR_RESET);
		fflush(stdout);
		rb_tree_print_colorful(node->left, k + 3);
	}
}

void rb_tree_print(RED_BLACK_NODE node, int k) {
	int i;
	if (node != NULL) {
		rb_tree_print(node->right, k + 3);
		if (k == 0)
			printf("t->:");
		else
			printf("    ");
		for (i = 0; i < k; i++) {
			printf(" ");
		}
		printf("%lu\n", node->key);
		fflush(stdout);
		rb_tree_print(node->left, k + 3);
	}
}

//freeing code
void free_rb_tree(RED_BLACK_NODE node) {
	if (node == NULL)
		return;
	free_rb_tree(node->left);
	free_rb_tree(node->right);
	if (node->data != NULL)
		free(node->data);
	free(node);
}

#endif /* REDBLACKTREE_H_ */
