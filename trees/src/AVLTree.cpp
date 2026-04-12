#include "../include/AVLTree.hpp"
#include <algorithm>


int AVLTree::height(Node* p) const {
    return p ? p->height : -1;
}

void AVLTree::fixheight(Node* p) {
    if (!p) return;
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = std::max(hl, hr) + 1;
}

int AVLTree::bfactor(Node* p) const {
    return height(p->right) - height(p->left);
}

AVLTree::Node* AVLTree::rotateRight(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

AVLTree::Node* AVLTree::rotateLeft(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

AVLTree::Node* AVLTree::balance(Node* p) {
    fixheight(p);
    if (bfactor(p) >= 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateRight(p->right);
        return rotateLeft(p);
    }
    if (bfactor(p) <= -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateLeft(p->left);
        return rotateRight(p);
    }
    return p;
}

bool AVLTree::insert(int value) {
    bool inserted = false;
    root = insert(root, value, inserted);
    if (inserted) tree_size++;
    return inserted;
}

AVLTree::Node* AVLTree::insert(Node* p, int k, bool& inserted) {
    if (!p) {
        inserted = true;
        return new Node(k);
    }
    if (k < p->key)
        p->left = insert(p->left, k, inserted);
    else if (k > p->key)
        p->right = insert(p->right, k, inserted);
    else {
        inserted = false;
        return p;
    }
    return balance(p);
}

bool AVLTree::remove(int value) {
    bool removed = false;
    root = remove(root, value, removed);
    if (removed) tree_size--;
    return removed;
}

AVLTree::Node* AVLTree::findMin(Node* p) const {
    return p->left ? findMin(p->left) : p;
}

AVLTree::Node* AVLTree::remove(Node* p, int k, bool& removed) {
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k, removed);
    else if (k > p->key)
        p->right = remove(p->right, k, removed);
    else {
        removed = true;
        if (!p->left) {
            Node* right = p->right;
            delete p;
            return right;
        }
        if (!p->right) {
            Node* left = p->left;
            delete p;
            return left;
        }
        Node* minNode = findMin(p->right);
        p->key = minNode->key;
        p->right = removeMin(p->right);
        return balance(p);
    }
    return balance(p);
}

AVLTree::Node* AVLTree::removeMin(Node* p) {
    if (!p->left) {
        Node* right = p->right;
        delete p;
        return right;
    }
    p->left = removeMin(p->left);
    return balance(p);
}

bool AVLTree::contains(int value) const {
    Node* curr = root;
    while (curr) {
        if (curr->key == value) return true;
        curr = (value < curr->key) ? curr->left : curr->right;
    }
    return false;
}

std::size_t AVLTree::size() const { return tree_size; }

bool AVLTree::empty() const { return root == nullptr; }

std::vector<int> AVLTree::values() const {
    std::vector<int> result;
    collectValues(root, result);
    return result;
}

void AVLTree::collectValues(Node* p, std::vector<int>& v) const {
    if (!p) return;
    collectValues(p->left, v);
    v.push_back(p->key);
    collectValues(p->right, v);
}

void AVLTree::clear(Node* p) {
    if (!p) return;
    clear(p->left);
    clear(p->right);
    delete p;
}

AVLTree::~AVLTree() {
    clear(root);
}