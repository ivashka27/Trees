#include "include/AVLTree.hpp"
#include <iostream>

int main() {
  AVLTree tree;

  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(50);
  tree.insert(40);
  tree.insert(25);

  tree.insert(10);
  tree.remove(30);
  tree.insert(68);
  tree.remove(50);

  std::cout << "Tree size: " << tree.size() << std::endl;
  std::cout << "Tree values: ";
  for (int val : tree.values()) {
    std::cout << val << " ";
  }
  std::cout << std::endl;

  return 0;
}