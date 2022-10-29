# Red-Black tree implementation in C and C++

## Usage in C
### Macros
#### Macro `RBTREE_DECL_STRUCTS(Name, Node, K, T)` is used to declare a Red-Black tree struct and node struct.
- `Name`: Name of the main tree struct.
- `Node`: Name of the tree node struct.
- `K`: Key type.
- `T`: Value type.
#### Macro `RBTREE_IMPL(Name, Node, K, T, Mods...)` is used to define the Red-Black tree functions.
- `Name`: Name of the main tree struct.
- `Node`: Name of the tree node struct.
- `K`: Key type.
- `T`: Value type.
- `Mods`: Optional modifiers to apply to before function definitions,
like `static` can be used to keep the tree functions local to a file.
#### Macro `RBTREE_DECL_FUNCTIONS(Name, Node, K, T)` is used to forward-declare the functions.
### Code Example
```c
#include "rb_tree.h"
#include "rb_tree_def.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int my_int;
} Data;

RBTREE_DECL_STRUCTS(RBTree, Node, int, int)
RBTREE_IMPL(RBTree, Node, int, int)

int main() {
	RBTree tree = RBTree_new();
	
	// New nodes can be allocated however you like
	Node* node = malloc(sizeof(Node));
	
	// Inserting a new value into the tree
	RBTree_insert(&tree, 0, (Data) {10}, node);
	
	// Getting the height of the tree
	intmax_t height = RBTree_height(&tree);
	
	// Searching from the tree
	Node* searchedNode = RBTree_search(&tree, 10);
	printf("%d\n", searchedNode->value);
	
	// Getting the successor of a node
	Node* successor = RBTree_successor(&tree, searchedNode);
	
	// Getting the predecessor of a node
	Node* predecessor = RBTree_predecessor(&tree, searchedNode);
	
	// Deleting from the tree
	Node* deletedNode = RBTree_remove(&tree, searchedNode);
	
	// deletedNode can now be freed
	free(deletedNode);
}
```

## Usage in C++
```cpp
#include "rb_tree.hpp"
#include <iostream>

struct Data {
	int my_int;
};

int main() {
	RBTree<int, Data> tree;
	
	// New nodes can be allocated anywhere you would like
	auto node = new RBTree<int, Data>::Node();
	
	// Inserting a new value into the tree
	tree.insert(0, Data(10), node);
	
	// Getting the height of the tree
	intmax_t height = tree.height();
	
	// Searching from the tree
	auto searchedNode = tree.search(10);
	std::cout << searchedNode->value << std::endl;
	
	// Getting the successor of a node
	auto successor = tree.successor(searchedNode);
	
	// Getting the predecessor of a node
	auto predecessor = tree.predecessor(searchedNode);
	
	// Deleting from the tree
	auto deletedNode = tree.remove(searchedNode);
	
	// deletedNode can now be freed
	delete deletedNode;
}
```