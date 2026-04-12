#pragma once

#include <vector>

class AVLTree {
private:
  struct Node {
    int value;
    int height;
    Node *left;
    Node *right;

    // what requirements says about height?
    Node(int v) : value(v), height(0), left(nullptr), right(nullptr){};
  };

  Node *root = nullptr;
  std::size_t tree_size = 0;

  int getHeight(Node *node) const;
  int getBalance(Node *node) const;
  void updateHeight(Node *node);

  Node *rotateLeft(Node *node);
  Node *rotateRight(Node *node);
  Node *balanceNode(Node *node);

  bool _contains(Node *node, int v) const;
  Node *_insert(Node *node, int v, bool &is_success);
  Node *_remove(Node *node, int v, bool &is_success);
  void depthFirstSearch(Node *node, std::vector<int> &vals) const;
  void destroyTree(Node *node);

public:
  bool contains(int value) const;
  bool insert(int value);
  bool remove(int value);

  std::size_t size() const;
  bool empty() const;

  std::vector<int> values() const;

  ~AVLTree();
};