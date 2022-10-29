#include "rb_tree.h"
#include "rb_tree_def.h"
#include <stdio.h>
#include <stdlib.h>

RBTREE_DECL_STRUCTS(RBTree, Node, int, int)
RBTREE_IMPL(RBTree, Node, int, int)

int main() {
	RBTree tree = RBTree_new();
	for (size_t i = 0; i < 1000; ++i) {
		Node* node = malloc(sizeof(Node));
		RBTree_insert(&tree, i, i, node);
	}
	printf("height with 1000 nodes: %jd\n", RBTree_height(&tree));
	printf("successor of node 2: %d\n", RBTree_successor(&tree, RBTree_search(&tree, 2))->key);
	printf("predecessor of node 2: %d\n", RBTree_predecessor(&tree, RBTree_search(&tree, 2))->key);
	for (size_t i = 0; i < 1000; ++i) {
		Node* node = RBTree_search(&tree, i);
		printf("found node %d\n", node->key);
		RBTree_remove(&tree, node);
	}
	printf("height with 0 nodes: %jd\n", RBTree_height(&tree));
}