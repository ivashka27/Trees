#include "AVLTree.h"


struct AVLTree::Node {
    int value;
    int height;
    Node* left;
    Node* right;

    Node(int v) : value(v), height(0), left(nullptr), right(nullptr) {}
};


int AVLTree::height(Node* node) const {
    return node ? node->height : -1;
}

void AVLTree::updateHeight(Node* node) {
    node->height = std::max(height(node->left), height(node->right)) + 1;
}

int AVLTree::balanceFactor(Node* node) const {
    return height(node->right) - height(node->left);
}


AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    updateHeight(x);
    updateHeight(y);

    return y;
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    updateHeight(y);
    updateHeight(x);

    return x;
}


AVLTree::Node* AVLTree::balance(Node* node) {
    updateHeight(node);

    int bf = balanceFactor(node);

    if (bf == 2) {
        if (balanceFactor(node->right) < 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    if (bf == -2) {
        if (balanceFactor(node->left) > 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}


AVLTree::Node* AVLTree::insertNode(Node* node, int value, bool& inserted) {
    if (!node) {
        inserted = true;
        return new Node(value);
    }

    if (value < node->value)
        node->left = insertNode(node->left, value, inserted);
    else if (value > node->value)
        node->right = insertNode(node->right, value, inserted);
    else
        return node;

    return balance(node);
}


AVLTree::Node* AVLTree::findMin(Node* node) const {
    return node->left ? findMin(node->left) : node;
}

AVLTree::Node* AVLTree::removeMin(Node* node) {
    if (!node->left)
        return node->right;

    node->left = removeMin(node->left);
    return balance(node);
}

AVLTree::Node* AVLTree::removeNode(Node* node, int value, bool& removed) {
    if (!node) return nullptr;

    if (value < node->value)
        node->left = removeNode(node->left, value, removed);
    else if (value > node->value)
        node->right = removeNode(node->right, value, removed);
    else {
        removed = true;

        Node* left = node->left;
        Node* right = node->right;

        delete node; // 💥 важно

        if (!right) return left;

        Node* min = findMin(right);
        min->right = removeMin(right);
        min->left = left;

        return balance(min);
    }

    return balance(node);
}


bool AVLTree::containsNode(Node* node, int value) const {
    if (!node) return false;

    if (value == node->value) return true;
    if (value < node->value)
        return containsNode(node->left, value);
    return containsNode(node->right, value);
}


void AVLTree::inorder(Node* node, std::vector<int>& res) const {
    if (!node) return;

    inorder(node->left, res);
    res.push_back(node->value);
    inorder(node->right, res);
}


void AVLTree::destroy(Node* node) {
    if (!node) return;

    destroy(node->left);
    destroy(node->right);
    delete node;
}


bool AVLTree::contains(int value) const {
    return containsNode(root, value);
}

bool AVLTree::insert(int value) {
    bool inserted = false;
    root = insertNode(root, value, inserted);
    if (inserted) sz++;
    return inserted;
}

bool AVLTree::remove(int value) {
    bool removed = false;
    root = removeNode(root, value, removed);
    if (removed) sz--;
    return removed;
}

std::size_t AVLTree::size() const {
    return sz;
}

bool AVLTree::empty() const {
    return sz == 0;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> res;
    inorder(root, res);
    return res;
}

AVLTree::~AVLTree() {
    destroy(root);
}