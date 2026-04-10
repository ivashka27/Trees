#include "AVLTree.hpp"

void AVLTree::destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}

int AVLTree::getHeight(Node* node) {
    return node ? node->height : -1;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* p = node->left;
    node->left = p->right;
    p->right = node;
    updateHeight(node);
    updateHeight(p);
    return p;
}

AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* p = node->right;
    node->right = p->left;
    p->left = node;
    updateHeight(node);
    updateHeight(p);
    return p;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    updateHeight(node);
    if (getBalance(node) == 2) {
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    if (getBalance(node) == -2) {
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    return node;
}

AVLTree::Node* AVLTree::insertInternal(Node* node, int value, bool& success) {
    if (!node) {
        success = true;
        return new Node(value);
    }
    if (value < node->value) {
        node->left = insertInternal(node->left, value, success);
    } else if (value > node->value) {
        node->right = insertInternal(node->right, value, success);
    } else {
        success = false;
        return node;
    }
    return balance(node);
}

AVLTree::Node* AVLTree::removeInternal(Node* node, int value, bool& success) {
    if (!node) {
        success = false;
        return nullptr;
    }
    if (value < node->value) {
        node->left = removeInternal(node->left, value, success);
    } else if (value > node->value) {
        node->right = removeInternal(node->right, value, success);
    } else {
        success = true;
        Node* left = node->left;
        Node* right = node->right;
        delete node;

        if (!right) return left;
        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;
        return balance(min);
    }
    return balance(node);
}

AVLTree::Node* AVLTree::findMin(Node* node) {
    return node->left ? findMin(node->left) : node;
}

AVLTree::Node* AVLTree::removeMin(Node* node) {
    if (!node->left) return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

void AVLTree::inOrder(Node* node, std::vector<int>& vec) const {
    if (!node) return;
    inOrder(node->left, vec);
    vec.push_back(node->value);
    inOrder(node->right, vec);
}

AVLTree::~AVLTree() {
    destroy(root);
}

bool AVLTree::insert(int value) {
    bool success = false;
    root = insertInternal(root, value, success);
    if (success) _size++;
    return success;
}

bool AVLTree::remove(int value) {
    bool success = false;
    root = removeInternal(root, value, success);
    if (success) _size--;
    return success;
}

bool AVLTree::contains(int value) const {
    Node* curr = root;
    while (curr) {
        if (value > curr->value) curr = curr->right;
        else if (value < curr->value) curr = curr->left;
        else return true;
    }
    return false;
}

std::size_t AVLTree::size() const { return _size; }
bool AVLTree::empty() const { return root == nullptr; }

std::vector<int> AVLTree::values() const {
    std::vector<int> result;
    result.reserve(_size);
    inOrder(root, result);
    return result;
}
