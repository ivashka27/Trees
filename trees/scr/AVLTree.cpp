#include "AVLTree.hpp"
#include <algorithm>

// helpful methods
int AVLTree::get_h(Node* node) const {
    if (node == nullptr) { return -1; }
    else { return node->height; }
}

void AVLTree::update_h(Node* node) {
    node->height = 1 + std::max(get_h(node->left),get_h(node->right));
}

int AVLTree::difference(Node* node) const {
    return get_h(node->right) - get_h(node->left);
}

AVLTree::Node* AVLTree::rotate_left(Node* node) {
    Node* new_node = node->right;
    node->right = new_node->left;
    new_node->left = node;

    update_h(node);
    update_h(new_node);

    return new_node;
}

AVLTree::Node* AVLTree::rotate_right(Node* node) {
    Node* new_node = node->left;
    node->left = new_node->right;
    new_node->right = node;

    update_h(node);
    update_h(new_node);

    return new_node;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    update_h(node);
    if (difference(node) == 2) {
        if (difference(node->right) < 0) { node->right = rotate_right(node->right); }
        node = rotate_left(node);
    }
    if (difference(node) == -2) {
        if (difference(node->left) > 0) { node->left = rotate_left(node->left); }
        node = rotate_right(node);
    }

    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int val) {
    if (node == nullptr) { return new Node(val); }

    if (val < node->value) { node->left = insert(node->left, val); }
    else { node->right = insert(node->right, val); }
 
    node = balance(node);
    return node;
}

AVLTree::Node* AVLTree::min_val(Node* node) const {
    Node* curr = node;
    while (curr->left != nullptr) { curr = curr->left; }

    return curr;
}

AVLTree::Node* AVLTree::remove(Node* node, int val) {
    if (node == nullptr) { return nullptr; }

    if (val < node->value) { node->left = remove(node->left, val); }
    else if (val > node->value) { node->right = remove(node->right, val); }
    else {
        if (node->right == nullptr && node->left == nullptr) { //no children
            delete node;
            return nullptr;
        } else if (node->right == nullptr && node->left != nullptr) { //left child
            Node* temp = node->left;
            delete node;
            return temp;
        } else if (node->right != nullptr && node->left == nullptr) { //right child
            Node* temp = node->right;
            delete node;
            return temp;
        } else { //both children
            Node* temp = min_val(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
    }

    node = balance(node);
    return node;
}

void AVLTree::in_order(Node* node, std::vector<int>& values) const {
    if (node == nullptr) { return; }
    in_order(node->left, values);
    values.push_back(node->value);
    in_order(node->right, values);
}

void AVLTree::clear(Node* node) {
    if (node == nullptr) { return; }
    clear(node->left);
    clear(node->right);
    delete node;
}



// main methods
bool AVLTree::contains(int value) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (value == curr->value) { return true; }
        else if (value < curr->value) { curr = curr->left; }
        else { curr = curr->right; }
    }
    return false;
}

bool AVLTree::insert(int value) {
    if (contains(value)) {return false;}

    root = insert(root, value);
    ++tree_size;
    return true;
}

bool AVLTree::remove(int value) {
    if (!contains(value)) {return false;}

    root = remove(root, value);
    --tree_size;
    return true;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::empty() const {
    if (tree_size == 0) { return true; }
    else { return false; }
}

std::vector<int> AVLTree::values() const {
    std::vector<int> vals;
    in_order(root, vals);
    return vals;
}

AVLTree::~AVLTree() {
    clear(root);
    root = nullptr;
    tree_size = 0;
}