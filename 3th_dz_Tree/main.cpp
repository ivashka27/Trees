#include <iostream>
#include "SplayTree.hpp"

int main() {
    SplayTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(7);

    std::cout << "Values: ";
    for (int x : tree.values()) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    std::cout << "Contains 7: " << tree.contains(7) << "\n";

    tree.remove(10);

    std::cout << "After remove 10: ";
    for (int x : tree.values()) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}