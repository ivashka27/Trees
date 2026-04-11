#include "AVLTree.hpp"
#include <algorithm>

AVLTree::AVLTree() : root(nullptr), count(0) {}

AVLTree::~AVLTree() {
    clear(root);
}

bool AVLTree::contains(int value) const {
    return contains(root, value);
}

bool AVLTree::insert(int value) {
    bool inserted = false;
    root = insert(root, value, inserted);
    return inserted;
}

bool AVLTree::remove(int value) {
    bool removed = false;
    root = remove(root, value, removed);
    return removed;
}

std::size_t AVLTree::size() const {
    return count;
}

bool AVLTree::empty() const {
    return count == 0;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> result;
    collectValues(root, result);
    return result;
}

//Приватные методы

int AVLTree::height(Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::balanceFactor(Node* node) const {
    return node ? height(node->left) - height(node->right) : 0;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    updateHeight(node);
    int bf = balanceFactor(node);

    if (bf > 1) {
        if (balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    
    if (bf < -1) {
        if (balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int value, bool& inserted) {
    if (!node) {
        inserted = true;
        ++count;
        return new Node(value);
    }

    if (value < node->value) {
        node->left = insert(node->left, value, inserted);
    } else if (value > node->value) {
        node->right = insert(node->right, value, inserted);
    } else {
        return node;
    }

    return balance(node);
}

AVLTree::Node* AVLTree::remove(Node* node, int value, bool& removed) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = remove(node->left, value, removed);
    } else if (value > node->value) {
        node->right = remove(node->right, value, removed);
    } else {
        removed = true;
        --count;

        if (!node->left || !node->right) {
            Node* temp = node->left ? node->left : node->right;
            if (!temp) {
                delete node;
                return nullptr;
            } else {
                delete node;
                return temp;
            }
        } else {
            Node* minRight = findMin(node->right);
            node->value = minRight->value;
            node->right = remove(node->right, minRight->value, removed);
            ++count;
            bool dummy = false;
            node->right = remove(node->right, minRight->value, dummy);
        }
    }

    return balance(node);
}

AVLTree::Node* AVLTree::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

bool AVLTree::contains(Node* node, int value) const {
    if (!node) return false;
    if (value < node->value) return contains(node->left, value);
    if (value > node->value) return contains(node->right, value);
    return true;
}

void AVLTree::collectValues(Node* node, std::vector<int>& result) const {
    if (!node) return;
    collectValues(node->left, result);
    result.push_back(node->value);
    collectValues(node->right, result);
}

void AVLTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}