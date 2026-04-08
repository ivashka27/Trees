#include "SplayTree.hpp"
#include <algorithm>

void SplayTree::rotate(Node* x) {
    Node* p = x->parent;
    Node* g = p->parent;

    if (p->left == x) {
        p->left = x->right;
        if (x->right) x->right->parent = p;
        x->right = p;
    }
    else {
        p->right = x->left;
        if (x->left) x->left->parent = p;
        x->left = p;
    }

    p->parent = x;
    x->parent = g;

    if (g) {
        if (g->left == p) g->left = x;
        else g->right = x;
    }
    else {
        root = x;
    }
}

void SplayTree::splay(Node* x) {
    if (!x) return;

    while (x->parent) {
        Node* p = x->parent;
        Node* g = p->parent;

        if (!g) {
            rotate(x);
        }
        else if ((g->left == p) == (p->left == x)) {
            rotate(p);
            rotate(x);
        }
        else {
            rotate(x);
            rotate(x);
        }
    }
    root = x;
}

SplayTree::Node* SplayTree::find(int value) const {
    Node* current = root;
    Node* last = nullptr;

    while (current) {
        last = current;
        if (value < current->value) {
            current = current->left;
        }
        else if (value > current->value) {
            current = current->right;
        }
        else {
            const_cast<SplayTree*>(this)->splay(current);
            return current;
        }
    }

    if (last) {
        const_cast<SplayTree*>(this)->splay(last);
    }
    return nullptr;
}

SplayTree::Node* SplayTree::findMax(Node* node) const {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    const_cast<SplayTree*>(this)->splay(node);
    return node;
}

SplayTree::Node* SplayTree::findMin(Node* node) const {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    const_cast<SplayTree*>(this)->splay(node);
    return node;
}

void SplayTree::split(Node*& t, int key, Node*& left, Node*& right) {
    if (!t) {
        left = right = nullptr;
        return;
    }

    splay(t);
    if (t->value <= key) {
        left = t;
        right = t->right;
        if (right) right->parent = nullptr;
        t->right = nullptr;
    }
    else {
        right = t;
        left = t->left;
        if (left) left->parent = nullptr;
        t->left = nullptr;
    }
}

SplayTree::Node* SplayTree::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    Node* maxLeft = findMax(left);
    splay(maxLeft);
    maxLeft->right = right;
    right->parent = maxLeft;
    return maxLeft;
}

bool SplayTree::contains(int value) const {
    return find(value) != nullptr;
}

bool SplayTree::insert(int value) {
    if (contains(value)) {
        return false;
    }

    Node* newNode = new Node(value);
    Node* left = nullptr;
    Node* right = nullptr;

    split(root, value, left, right);

    newNode->left = left;
    if (left) left->parent = newNode;
    newNode->right = right;
    if (right) right->parent = newNode;

    root = newNode;
    splay(newNode);
    treeSize++;
    return true;
}

bool SplayTree::remove(int value) {
    Node* node = find(value);
    if (!node) {
        return false;
    }

    splay(node);
    Node* left = node->left;
    Node* right = node->right;

    if (left) left->parent = nullptr;
    if (right) right->parent = nullptr;

    delete node;

    root = merge(left, right);
    treeSize--;
    return true;
}

std::size_t SplayTree::size() const {
    return treeSize;
}

bool SplayTree::empty() const {
    return treeSize == 0;
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}

void SplayTree::inorder(Node* node, std::vector<int>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

void SplayTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

SplayTree::~SplayTree() {
    clear(root);
}
