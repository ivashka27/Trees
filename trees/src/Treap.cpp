#include "../include/Treap.hpp"

#include <cstdlib>
#include <vector>

struct Treap::Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k)
        : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

void Treap::split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
    } else if (key > node->key) {
        split(node->right, key, node->right, right);
        left = node;
    } else {
        split(node->left, key, left, node->left);
        right = node;
    }
}

Treap::Node* Treap::merge(Node* left, Node* right) {
    if (!left || !right)
        return left ? left : right;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    } else {
        right->left = merge(left, right->left);
        return right;
    }
}

bool Treap::contains(Node* node, int key) const {
    if (!node) return false;
    if (node->key == key) return true;

    if (key < node->key)
        return contains(node->left, key);
    else
        return contains(node->right, key);
}

Treap::Node* Treap::remove(Node* node, int key, bool& removed) {
    if (!node) return nullptr;

    if (node->key == key) {
        removed = true;
        Node* res = merge(node->left, node->right);
        delete node;
        return res;
    }

    if (key < node->key)
        node->left = remove(node->left, key, removed);
    else
        node->right = remove(node->right, key, removed);

    return node;
}

void Treap::inorder(Node* node, std::vector<int>& res) const {
    if (!node) return;

    inorder(node->left, res);
    res.push_back(node->key);
    inorder(node->right, res);
}

void Treap::clear(Node* node) {
    if (!node) return;

    clear(node->left);
    clear(node->right);
    delete node;
}


bool Treap::contains(int value) const {
    return contains(root, value);
}

bool Treap::insert(int value) {
    if (contains(value)) return false;

    Node *L, *R;
    split(root, value, L, R);

    Node* newNode = new Node(value);
    root = merge(merge(L, newNode), R);

    ++sz;
    return true;
}

bool Treap::remove(int value) {
    bool removed = false;
    root = remove(root, value, removed);

    if (removed) --sz;
    return removed;
}

std::size_t Treap::size() const {
    return sz;
}

bool Treap::empty() const {
    return sz == 0;
}

std::vector<int> Treap::values() const {
    std::vector<int> res;
    inorder(root, res);
    return res;
}

Treap::~Treap() {
    clear(root);
}