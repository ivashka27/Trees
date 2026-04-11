#include "SplayTree.hpp"
#include <algorithm>

SplayTree::SplayTree() : root(nullptr), tree_size(0) {}

void SplayTree::destroySubtree(Node* node) {
    if (!node) return;
    destroySubtree(node->left);
    destroySubtree(node->right);
    delete node;
}

SplayTree::~SplayTree() {
    destroySubtree(root);
}

void SplayTree::clear() {
    destroySubtree(root);
    root = nullptr;
    tree_size = 0;
}

void SplayTree::rotateLeft(Node* x) const {
    if (!x || !x->right) return;
    Node* y = x->right;
  
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (!x->parent) {
        root = y;  // x был корнем
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void SplayTree::rotateRight(Node* x) const {
    if (!x || !x->left) return;
    Node* y = x->left;

    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }

    y->right = x;
    x->parent = y;
}

void SplayTree::splay(Node* x) const {
    if (!x) return;

    while (x->parent) {
        Node* p = x->parent;
        Node* g = p->parent;

        if (!g) {
            if (x == p->left) {
                rotateRight(p);
            } else {
                rotateLeft(p);
            }
        } 
        else if (x == p->left && p == g->left) {
            rotateRight(g);
            rotateRight(p);
        } 
        else if (x == p->right && p == g->right) {
            rotateLeft(g);
            rotateLeft(p);
        } 
        else if (x == p->right && p == g->left) {
            rotateLeft(p);
            rotateRight(g);
        } 
        else {
            rotateRight(p);
            rotateLeft(g);
        }
    }
    root = x;
}

SplayTree::Node* SplayTree::findNode(int value) const {
    Node* cur = root;
    Node* last = nullptr;

    while (cur) {
        last = cur;
        if (value == cur->key) {
            return cur;
        } else if (value < cur->key) {
            cur = cur->left;
        } else {
            cur = cur->right;
        }
    }
    return last;
}

SplayTree::Node* SplayTree::getMaximum(Node* node) const {
    if (!node) return nullptr;
    while (node->right) {
        node = node->right;
    }
    return node;
}

void SplayTree::inorderTraversal(Node* node, std::vector<int>& result) const {
    if (!node) return;
    inorderTraversal(node->left, result);
    result.push_back(node->key);
    inorderTraversal(node->right, result);
}

bool SplayTree::contains(int value) const {
    if (!root) return false;

    Node* node = findNode(value);
    
    if (node && node->key == value) {
        splay(node);
        return true;
    }
    
    if (node) {
        splay(node);
    }
    
    return false;
}

bool SplayTree::insert(int value) {
    if (!root) {
        root = new Node(value);
        ++tree_size;
        return true;
    }

    Node* node = findNode(value);

    if (node && node->key == value) {
        splay(node);
        return false;
    }

    Node* newNode = new Node(value);
    ++tree_size;

    if (value < node->key) {
        node->left = newNode;
    } else {
        node->right = newNode;
    }
    newNode->parent = node;

    splay(newNode);

    return true;
}

bool SplayTree::remove(int value) {
    if (!root) return false;

    Node* node = findNode(value);
    
    if (!node || node->key != value) {
        if (node) splay(node);
        return false;
    }

    splay(node);

    Node* leftSub = root->left;
    Node* rightSub = root->right;

    delete root;
    --tree_size;

    if (!leftSub && !rightSub) {
        root = nullptr;
        return true;
    }

    if (!leftSub) {
        root = rightSub;
        root->parent = nullptr;
        return true;
    }

    if (!rightSub) {
        root = leftSub;
        root->parent = nullptr;
        return true;
    }

    root = leftSub;
    root->parent = nullptr;

    Node* maxInLeft = getMaximum(root);
    splay(maxInLeft);

    root->right = rightSub;
    rightSub->parent = root;

    return true;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    result.reserve(tree_size);
    inorderTraversal(root, result);
    return result;
}
