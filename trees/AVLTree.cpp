#include "include/AVLTree.hpp"
#include <algorithm>
#include <cstddef>
#include <iostream>

AVLTree::~AVLTree() { destroyTree(root); }

void AVLTree::destroyTree(Node *node) {
  if (node != nullptr) {
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
    tree_size--;
  }
}

int AVLTree::getHeight(Node *node) const {
  return node == nullptr ? 0 : node->height;
}

int AVLTree::getBalance(Node *node) const {
  if (node == nullptr) {
    return 0;
  }
  return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::updateHeight(Node *node) {
  if (node != nullptr) {
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
  }
}

std::size_t AVLTree::size() const { return tree_size; }

bool AVLTree::empty() const { return root == nullptr; }

bool AVLTree::contains(int value) const {
  return AVLTree::_contains(root, value);
}

bool AVLTree::_contains(Node *node, int v) const {
  if (node == nullptr)
    return false;
  if (node->value == v)
    return true;
  if (v < node->value)
    return _contains(node->left, v);
  else
    return _contains(node->right, v);
}

std::vector<int> AVLTree::values() const {
  std::vector<int> vals;
  vals.reserve(size()); // prevent reallocations
  depthFirstSearch(root, vals);
  return vals;
}

// Using recursion instead of iteration because it's more concise
// and the stack depth is limited by the height of the tree
// which is O(log n) for an AVL tree (no performance gains from iteration)
void AVLTree::depthFirstSearch(Node *node, std::vector<int> &vals) const {
  if (node != nullptr) {
    depthFirstSearch(node->left, vals);
    vals.push_back(node->value);
    depthFirstSearch(node->right, vals);
  }
}

AVLTree::Node *AVLTree::_insert(Node *node, int v, bool &is_success) {
  if (node == nullptr) {
    is_success = true;
    return new Node(v);
  }

  if (node->value == v) {
    is_success = false;
    return node;
  }

  if (node->value < v) {
    node->right = _insert(node->right, v, is_success);
  } else {
    node->left = _insert(node->left, v, is_success);
  }

  updateHeight(node);
  return balanceNode(node);
}

bool AVLTree::insert(int value) {
  bool is_success = false;
  root = _insert(root, value, is_success);

  if (is_success) {
    tree_size++;
  }

  return is_success;
}

AVLTree::Node *AVLTree::_remove(Node *node, int v, bool &is_success) {
  if (node == nullptr) {
    is_success = false;
    return nullptr;
  }

  if (node->value < v) {
    node->right = _remove(node->right, v, is_success);
  } else if (node->value > v) {
    node->left = _remove(node->left, v, is_success);
  }

  else { // found
    is_success = true;
    if (node->left == nullptr) {
      Node *temp = node->right;
      delete node;
      return temp;
    } else if (node->right == nullptr) {
      Node *temp = node->left;
      delete node;
      return temp;
    }

    Node *temp = node->right;
    while (temp->left) {
      temp = temp->left;
    }
    node->value = temp->value;

    // save to pass is_success because temp value exists
    node->right = _remove(node->right, temp->value, is_success);
  }

  updateHeight(node);
  return balanceNode(node);
}

bool AVLTree::remove(int value) {
  bool is_success = false;
  root = _remove(root, value, is_success);

  if (is_success) {
    tree_size--;
  }

  return is_success;
}

AVLTree::Node *AVLTree::balanceNode(Node *node) {
  int balance = getBalance(node);

  if (balance > 1) {
    if (getBalance(node->left) < 0) {
      node->left = rotateLeft(node->left);
    }
    return rotateRight(node);
  } else if (balance < -1) {
    if (getBalance(node->right) > 0) {
      node->right = rotateRight(node->right);
    }
    return rotateLeft(node);
  }

  return node;
}

AVLTree::Node *AVLTree::rotateRight(Node *node) {
  Node *left = node->left;
  Node *grandRight = left->right;

  left->right = node;
  node->left = grandRight;

  // Order matters!
  updateHeight(node);
  updateHeight(left);

  return left;
}

AVLTree::Node *AVLTree::rotateLeft(Node *node) {
  Node *right = node->right;
  Node *grandLeft = right->left;

  right->left = node;
  node->right = grandLeft;

  // Order matters!
  updateHeight(node);
  updateHeight(right);

  return right;
}
