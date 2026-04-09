#include "../include/SplayTree.hpp"

// rotations

void SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    if (!y) return;

    x->right = y->left;
    if (y->left) y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    if (!y) return;

    x->left = y->right;
    if (y->right) y->right->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->right = x;
    x->parent = y;
}

// splay

void SplayTree::splay(Node* x) {
    while (x->parent) {
        if (!x->parent->parent) {
            if (x->parent->left == x)
                rotateRight(x->parent);
            else
                rotateLeft(x->parent);
        }
        else if (x->parent->left == x && x->parent->parent->left == x->parent) {
            rotateRight(x->parent->parent);
            rotateRight(x->parent);
        }
        else if (x->parent->right == x && x->parent->parent->right == x->parent) {
            rotateLeft(x->parent->parent);
            rotateLeft(x->parent);
        }
        else {
            if (x->parent->left == x) {
                rotateRight(x->parent);
                rotateLeft(x->parent);
            } else {
                rotateLeft(x->parent);
                rotateRight(x->parent);
            }
        }
    }
}

// find

SplayTree::Node* SplayTree::find(int value) const {
    Node* cur = root;
    while (cur) {
        if (value == cur->value)
            return cur;
        else if (value < cur->value)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return nullptr;
}

// contains

bool SplayTree::contains(int value) const {
    Node* node = find(value);
    if (!node) return false;

    const_cast<SplayTree*>(this)->splay(node);
    return true;
}

// insert

bool SplayTree::insert(int value) {
    if (!root) {
        root = new Node(value);
        tree_size++;
        return true;
    }

    Node* cur = root;
    Node* parent = nullptr;

    while (cur) {
        parent = cur;
        if (value == cur->value) {
            splay(cur);
            return false;
        }
        else if (value < cur->value)
            cur = cur->left;
        else
            cur = cur->right;
    }

    Node* node = new Node(value);
    node->parent = parent;

    if (value < parent->value)
        parent->left = node;
    else
        parent->right = node;

    splay(node);
    tree_size++;
    return true;
}

// remove

bool SplayTree::remove(int value) {
    Node* node = find(value);
    if (!node) return false;

    splay(node);

    if (!node->left) {
        root = node->right;
        if (root) root->parent = nullptr;
    } else {
        Node* leftSub = node->left;
        leftSub->parent = nullptr;

        Node* maxNode = leftSub;
        while (maxNode->right)
            maxNode = maxNode->right;

        splay(maxNode);

        maxNode->right = node->right;
        if (node->right)
            node->right->parent = maxNode;

        root = maxNode;
    }

    delete node;
    tree_size--;
    return true;
}

// values

void SplayTree::inorder(Node* node, std::vector<int>& res) const {
    if (!node) return;
    inorder(node->left, res);
    res.push_back(node->value);
    inorder(node->right, res);
}

std::vector<int> SplayTree::values() const {
    std::vector<int> res;
    inorder(root, res);
    return res;
}

// size/empty

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

// destructor

void SplayTree::deleteSubtree(Node* node) {
    if (!node) return;
    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}

SplayTree::~SplayTree() {
    deleteSubtree(root);
}
