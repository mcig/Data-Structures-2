#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generate_backbone(TREE t);
void regenerate_tree(TREE t, int nodeCount);

int main(int argc, char **argv) {
	TREE t = tree_init();
	int i, *keysArr, nodeCount = 7;
	srand(time(NULL));
	fill_tree_keys_with_unique_random_v2(t, nodeCount, nodeCount * 10,
			&keysArr);

	//Initial Tree
	tree_print(t->root, 0);
	printf("\n******************\n");

	//Backbone
	generate_backbone(t);
	tree_print(t->root, 0);
	printf("\n******************\n");

	//Final Balanced Tree
	regenerate_tree(t, nodeCount);
	tree_print(t->root, 0);
	//printf("\n******************\n");

	for (i = 0; i < nodeCount; i++) {
		tree_delete_node_balanced_iterative(t, keysArr[i]);
	}
	free(keysArr);
	tree_kill(t);
	return 0;
}

void right_rotation(TREE *t, NODE *pGp, NODE *pP, NODE *pC) {
	NODE gp = ((NODE) *pGp);
	NODE p = ((NODE) *pP);
	NODE c = ((NODE) *pC);

	p->left = c->right;
	c->right = p;
	if (gp == (NODE) *t)
		gp->left = c;
	else
		gp->right = c;
}

void generate_backbone(TREE t) {
	NODE gp, p, c;
	gp = (NODE) t;
	p = gp->left;
	while (p != NULL) {
		c = p->left;
		if (c == NULL) {
			gp = p;
			p = p->right;
		} else {
			right_rotation(&t, &gp, &p, &c);
			p = c;
		}
	}
}

void left_rotation(TREE *t, NODE *pGp, NODE *pP, NODE *pC) {
	NODE gp = ((NODE) *pGp);
	NODE p = ((NODE) *pP);
	NODE c = ((NODE) *pC);

	p->right = c->left;
	c->left = p;
	if (gp == (NODE) *t)
		gp->left = c;
	else
		gp->right = c;
}

void regenerate_tree(TREE t, int nodeCount) {
	int i, m = pow(2, (int) log2((int) (nodeCount + 1))) - 1;
	NODE gp, p, c;
	gp = (NODE) t;
	p = gp->left;
	c = p->right;

	for (i = 0; i < nodeCount - m; i++) {
		left_rotation(&t, &gp, &p, &c);
		gp = c;
		p = c->right;
		c = p->right;
	}

	while (m > 1) {
		m /= 2;
		gp = (NODE) t;
		p = gp->left;
		c = p->right;
		for (i = 0; i < m; i++) {
			left_rotation(&t, &gp, &p, &c);
			gp = c;
			p = c->right;
			c = p->right;
		}
	}
}
