#include <iostream>
#include "rb_tree.hpp"

int main() {
	RBTree<int, int> tree {};

	for (size_t i = 0; i < 1000; ++i) {
		auto node = new RBTree<int, int>::Node(0, 0);
		tree.insert(i, i, node);
	}
	std::cout << "height with 1000 nodes: " << tree.height() << std::endl;

	std::cout << "successor of node 2: " << tree.successor(tree.search(2))->key << std::endl;
	std::cout << "predecessor of node 2: " << tree.predecessor(tree.search(2))->key << std::endl;

	for (size_t i = 0; i < 1000; ++i) {
		auto node = tree.search(i);
		if (node) std::cout << "found node " << i << std::endl;
		tree.remove(node);
	}
	std::cout << "height with 0 nodes: " << tree.height() << std::endl;

	return 0;
}
