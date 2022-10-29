#include "rb_tree.h"

#define RBTREE_COLOR_BLACK 0
#define RBTREE_COLOR_RED 1

#define RBTREE_IMPL(Name, Node, K, T, Mods...) \
Mods Name CONCAT(Name, _new()) { \
	Name tree = {NULL, {0}}; \
	tree.root = &tree.null; \
	return tree; \
} \
\
static inline Node* CONCAT(Name, _min)(Name* self, Node* node) { \
	while (node->left != &self->null) node = node->left; \
	return node; \
} \
\
static inline Node* CONCAT(Name, _max)(Name* self, Node* node) { \
	while (node->right != &self->null) node = node->right; \
	return node; \
} \
\
static inline void CONCAT(Name, _rotate_left)(Name* self, Node* node) { \
	Node* new_root = node->right; \
	node->right = new_root->left; \
	if (new_root->left != &self->null) new_root->left->parent = node; \
	new_root->parent = node->parent; \
	if (node->parent == &self->null) self->root = new_root; \
	else if (node == node->parent->left) node->parent->left = new_root; \
	else node->parent->right = new_root; \
	new_root->left = node; \
	node->parent = new_root; \
} \
\
static inline void CONCAT(Name, _rotate_right)(Name* self, Node* node) { \
	Node* new_root = node->left; \
	node->left = new_root->right; \
	if (new_root->right != &self->null) new_root->right->parent = node; \
	new_root->parent = node->parent; \
	if (node->parent == &self->null) self->root = new_root; \
	else if (node == node->parent->left) node->parent->left = new_root; \
	else node->parent->right = new_root; \
	new_root->right = node; \
	node->parent = new_root; \
} \
\
static inline void CONCAT(Name, _transplant)(Name* self, Node* replace, Node* with) { \
	if (replace->parent == &self->null) self->root = with; \
	else if (replace == replace->parent->left) replace->parent->left = with; \
	else replace->parent->right = with; \
	with->parent = replace->parent; \
} \
\
static inline void CONCAT(Name, _insert_fix)(Name* self, Node* node) { \
	while (node->parent->color == RBTREE_COLOR_RED) { \
		Node* parent = node->parent; \
		Node* grandparent = parent->parent; \
		if (parent == grandparent->left) { \
			Node* uncle = grandparent->right; \
			if (uncle->color == RBTREE_COLOR_RED) { \
				parent->color = RBTREE_COLOR_BLACK; \
				uncle->color = RBTREE_COLOR_BLACK; \
				grandparent->color = RBTREE_COLOR_RED; \
				node = grandparent; \
			} \
			else { \
				if (node == parent->right) { \
					node = parent; \
					CONCAT(Name, _rotate_left)(self, node); \
				} \
				node->parent->color = RBTREE_COLOR_BLACK; \
				node->parent->parent->color = RBTREE_COLOR_RED; \
				CONCAT(Name, _rotate_right)(self, node->parent->parent); \
			} \
		} \
		else { \
			Node* uncle = parent->parent->left; \
			if (uncle->color == RBTREE_COLOR_RED) { \
				parent->color = RBTREE_COLOR_BLACK; \
				uncle->color = RBTREE_COLOR_BLACK; \
				grandparent->color = RBTREE_COLOR_RED; \
				node = grandparent; \
			} \
			else { \
				if (node == parent->left) { \
					node = parent; \
					CONCAT(Name, _rotate_right)(self, node); \
				} \
				node->parent->color = RBTREE_COLOR_BLACK; \
				node->parent->parent->color = RBTREE_COLOR_RED; \
				CONCAT(Name, _rotate_left)(self, node->parent->parent); \
			} \
		} \
	} \
	\
	self->root->color = RBTREE_COLOR_BLACK; \
} \
\
static inline void CONCAT(Name, _delete_fix)(Name* self, Node* node) { \
	while (node != self->root && node->color == RBTREE_COLOR_BLACK) { \
		Node* parent = node->parent; \
		if (node == parent->left) { \
			Node* sibling = parent->right; \
			if (sibling->color == RBTREE_COLOR_RED) { \
				sibling->color = RBTREE_COLOR_BLACK; \
				parent->color = RBTREE_COLOR_RED; \
				CONCAT(Name, _rotate_left)(self, parent); \
				sibling = parent->right; \
			} \
			if (sibling->left->color == RBTREE_COLOR_BLACK && sibling->right->color == RBTREE_COLOR_BLACK) { \
				sibling->color = RBTREE_COLOR_RED; \
				node = sibling->parent; \
			} \
			else { \
				if (sibling->right->color == RBTREE_COLOR_BLACK) { \
					sibling->left->color = RBTREE_COLOR_BLACK; \
					sibling->color = RBTREE_COLOR_RED; \
					CONCAT(Name, _rotate_right)(self, sibling); \
					sibling = parent->right; \
				} \
				sibling->color = parent->color; \
				parent->color = RBTREE_COLOR_BLACK; \
				sibling->right->color = RBTREE_COLOR_BLACK; \
				CONCAT(Name, _rotate_left)(self, parent); \
				node = self->root; \
			} \
		} \
		else { \
			Node* sibling = parent->left; \
			if (sibling->color == RBTREE_COLOR_RED) { \
				sibling->color = RBTREE_COLOR_BLACK; \
				parent->color = RBTREE_COLOR_RED; \
				CONCAT(Name, _rotate_right)(self, parent); \
				sibling = parent->left; \
			} \
			if (sibling->right->color == RBTREE_COLOR_BLACK && sibling->left->color == RBTREE_COLOR_BLACK) { \
				sibling->color = RBTREE_COLOR_RED; \
				node = sibling->parent; \
			} \
			else { \
				if (sibling->left->color == RBTREE_COLOR_BLACK) { \
					sibling->right->color = RBTREE_COLOR_BLACK; \
					sibling->color = RBTREE_COLOR_RED; \
					CONCAT(Name, _rotate_left)(self, sibling); \
					sibling = parent->left; \
				} \
				sibling->color = parent->color; \
				parent->color = RBTREE_COLOR_BLACK; \
				sibling->left->color = RBTREE_COLOR_BLACK; \
				CONCAT(Name, _rotate_right)(self, parent); \
				node = self->root; \
			} \
		} \
	} \
} \
\
Mods void CONCAT(Name, _insert)(Name* self, K key, T value, Node* node) { \
	node->key = key; \
	node->value = value; \
	\
	Node* prev = &self->null; \
	Node* n = self->root; \
	while (n != &self->null) { \
		prev = n; \
		if (key < n->key) n = n->left; \
		else n = n->right; \
	} \
	node->parent = prev; \
	if (prev == &self->null) self->root = node; \
	else if (key < prev->key) prev->left = node; \
	else prev->right = node; \
	node->left = &self->null; \
	node->right = &self->null; \
	node->color = RBTREE_COLOR_RED; \
	CONCAT(Name, _insert_fix)(self, node); \
} \
\
Mods Node* CONCAT(Name, _remove)(Name* self, Node* node) { \
	char original_color = node->color; \
	Node* replace; \
	if (node->left == &self->null) { \
		replace = node->right; \
		CONCAT(Name, _transplant)(self, node, replace); \
	} \
	else if (node->right == &self->null) { \
		replace = node->left; \
		CONCAT(Name, _transplant)(self, node, replace); \
	} \
	else { \
		Node* successor = CONCAT(Name, _min)(self, node->right); \
		original_color = successor->color; \
		replace = successor->right; \
		if (successor->parent == node) replace->parent = successor; \
		else { \
			CONCAT(Name, _transplant)(self, successor, replace); \
			successor->right = node->right; \
			successor->right->parent = successor; \
		} \
		CONCAT(Name, _transplant)(self, node, successor); \
		successor->left = node->left; \
		successor->left->parent = successor; \
		successor->color = node->color; \
	} \
	if (original_color == RBTREE_COLOR_BLACK) { \
		CONCAT(Name, _delete_fix)(self, replace); \
	} \
	return replace; \
} \
\
Mods Node* CONCAT(Name, _search)(Name* self, K key) { \
	Node* node = self->root; \
	while (node != &self->null) { \
		if (key < node->key) node = node->left; \
		else if (key > node->key) node = node->right; \
		else return node; \
	} \
	return NULL; \
} \
\
Mods Node* CONCAT(Name, _successor)(Name* self, Node* node) { \
	if (node->right != &self->null) return CONCAT(Name, _min)(self, node->right); \
	Node* parent = node->parent; \
	while (parent != &self->null && node == parent->right) { \
		node = parent; \
		parent = parent->parent; \
	} \
	return parent; \
} \
\
Mods Node* CONCAT(Name, _predecessor)(Name* self, Node* node) { \
	if (node->left != &self->null) return CONCAT(Name, _max)(self, node->left); \
	Node* parent = node->parent; \
	while (parent != &self->null && node == parent->left) { \
		node = parent; \
		parent = parent->parent; \
	} \
	return parent; \
} \
\
static inline intmax_t CONCAT(Name, _height_internal)(Name* self, Node* node) { /* NOLINT(misc-no-recursion) */ \
	if (node == &self->null) return -1; \
	intmax_t left_height = CONCAT(Name, _height_internal)(self, node->left); \
	intmax_t right_height = CONCAT(Name, _height_internal)(self, node->right); \
	return (left_height > right_height ? left_height : right_height) + 1; \
} \
\
Mods intmax_t CONCAT(Name, _height)(Name* self) { \
	return CONCAT(Name, _height_internal)(self, self->root); \
}