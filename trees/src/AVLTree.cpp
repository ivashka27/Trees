#include "AVLTree.h"
#include <algorithm>

int AVLTree::height(Node* n) const { return n ? n->height : 0; }

int AVLTree::get_balance(Node* n) const {
    return n ? height(n->right) - height(n->left) : 0;
}

void AVLTree::update_height(Node* n) {
    if (n) n->height = 1 + std::max(height(n->left), height(n->right));
}

AVLTree::Node* AVLTree::rotate_right(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update_height(y);
    update_height(x);
    return x;
}

AVLTree::Node* AVLTree::rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update_height(x);
    update_height(y);
    return y;
}

AVLTree::Node* AVLTree::balance(Node* n) {
    update_height(n);
    int b = get_balance(n);
    if (b == 2) {
        if (get_balance(n->right) < 0) n->right = rotate_right(n->right);
        return rotate_left(n);
    }
    if (b == -2) {
        if (get_balance(n->left) > 0) n->left = rotate_left(n->left);
        return rotate_right(n);
    }
    return n;
}

AVLTree::Node* AVLTree::insert_recursive(Node* n, int val, bool& success) {
    if (!n) { success = true; return new Node(val); }
    if (val < n->value) n->left = insert_recursive(n->left, val, success);
    else if (val > n->value) n->right = insert_recursive(n->right, val, success);
    else success = false;
    return success ? balance(n) : n;
}

AVLTree::Node* AVLTree::find_min(Node* n) const {
    return n->left ? find_min(n->left) : n;
}

AVLTree::Node* AVLTree::remove_min(Node* n) {
    if (!n->left) return n->right;
    n->left = remove_min(n->left);
    return balance(n);
}

AVLTree::Node* AVLTree::remove_recursive(Node* n, int val, bool& success) {
    if (!n) return nullptr;
    if (val < n->value) n->left = remove_recursive(n->left, val, success);
    else if (val > n->value) n->right = remove_recursive(n->right, val, success);
    else {
        success = true;
        Node *l = n->left, *r = n->right;
        delete n;
        if (!r) return l;
        Node* min = find_min(r);
        min->right = remove_min(r);
        min->left = l;
        return balance(min);
    }
    return balance(n);
}

void AVLTree::clear(Node* n) {
    if (!n) return;
    clear(n->left);
    clear(n->right);
    delete n;
}

void AVLTree::traverse(Node* n, std::vector<int>& res) const {
    if (!n) return;
    traverse(n->left, res);
    res.push_back(n->value);
    traverse(n->right, res);
}

AVLTree::~AVLTree() { clear(root); }

bool AVLTree::contains(int value) const {
    Node* curr = root;
    while (curr) {
        if (value == curr->value) return true;
        curr = (value < curr->value) ? curr->left : curr->right;
    }
    return false;
}

bool AVLTree::insert(int value) {
    bool success = false;
    root = insert_recursive(root, value, success);
    if (success) tree_size++;
    return success;
}

bool AVLTree::remove(int value) {
    bool success = false;
    root = remove_recursive(root, value, success);
    if (success) tree_size--;
    return success;
}

std::size_t AVLTree::size() const { return tree_size; }
bool AVLTree::empty() const { return tree_size == 0; }

std::vector<int> AVLTree::values() const {
    std::vector<int> res;
    res.reserve(tree_size);
    traverse(root, res);
    return res;
}