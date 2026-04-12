#include "AVLTree.hpp"
#include <algorithm>

int AVLTree::get_h(Node* node) const {
    return node ? node->height : -1;
}

void AVLTree::update_h(Node* node) {
    node->height = 1 + std::max(get_h(node->left), get_h(node->right));
}

int AVLTree::difference(Node* node) const {
    return get_h(node->right) - get_h(node->left);
}

AVLTree::Node* AVLTree::rotate_left(Node* node) {
    Node* r = node->right;
    node->right = r->left;
    r->left = node;

    update_h(node);
    update_h(r);

    return r;
}

AVLTree::Node* AVLTree::rotate_right(Node* node) {
    Node* l = node->left;
    node->left = l->right;
    l->right = node;

    update_h(node);
    update_h(l);

    return l;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    update_h(node);

    if (difference(node) == 2) {
        if (difference(node->right) < 0)
            node->right = rotate_right(node->right);
        return rotate_left(node);
    }

    if (difference(node) == -2) {
        if (difference(node->left) > 0)
            node->left = rotate_left(node->left);
        return rotate_right(node);
    }

    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int value) {
    if (!node)
        return new Node(value);

    if (value < node->value)
        node->left = insert(node->left, value);
    else
        node->right = insert(node->right, value);

    return balance(node);
}

AVLTree::Node* AVLTree::min_val(Node* node) const {
    while (node->left)
        node = node->left;
    return node;
}

AVLTree::Node* AVLTree::remove(Node* node, int value) {
    if (!node)
        return nullptr;

    if (value < node->value) {
        node->left = remove(node->left, value);
    } else if (value > node->value) {
        node->right = remove(node->right, value);
    } else {
        if (!node->left || !node->right) {
            Node* tmp = node->left ? node->left : node->right;
            delete node;
            return tmp;
        }

        Node* m = min_val(node->right);
        node->value = m->value;
        node->right = remove(node->right, m->value);
    }

    return balance(node);
}

void AVLTree::in_order(Node* node, std::vector<int>& v) const {
    if (!node)
        return;

    in_order(node->left, v);
    v.push_back(node->value);
    in_order(node->right, v);
}

void AVLTree::clear(Node* node) {
    if (!node)
        return;

    clear(node->left);
    clear(node->right);
    delete node;
}



bool AVLTree::contains(int value) const {
    Node* cur = root;

    while (cur) {
        if (value == cur->value)
            return true;
        if (value < cur->value)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return false;
}

bool AVLTree::insert(int value) {
    if (contains(value))
        return false;

    root = insert(root, value);
    ++tree_size;
    return true;
}

bool AVLTree::remove(int value) {
    if (!contains(value))
        return false;

    root = remove(root, value);
    --tree_size;
    return true;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::empty() const {
    return tree_size == 0;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> v;
    in_order(root, v);
    return v;
}

AVLTree::~AVLTree() {
    clear(root);
}
