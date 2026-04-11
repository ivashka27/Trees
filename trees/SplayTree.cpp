#include "SplayTree.hpp"

SplayTree::Node::Node(int val)
    : value(val), left(nullptr), right(nullptr), parent(nullptr) {
}

SplayTree::SplayTree() : root(nullptr), tree_size(0) {}

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    if (y == nullptr) return;

    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}

void SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    if (y == nullptr) return;

    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}

void SplayTree::splay(Node* x) {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent;

        if (g == nullptr) {
            if (x == p->left) {
                rotateRight(p);
            }
            else {
                rotateLeft(p);
            }
        }
        else if (x == p->left && p == g->left) {
            rotateRight(g);
            rotateRight(p);
        }
        else if (x == p->right && p == g->right) {
            rotateLeft(g);
            rotateLeft(p);
        }
        else if (x == p->right && p == g->left) {
            rotateLeft(p);
            rotateRight(g);
        }
        else {
            rotateRight(p);
            rotateLeft(g);
        }
    }
}

SplayTree::Node* SplayTree::findNode(int value) {
    Node* current = root;
    Node* prev = nullptr;

    while (current != nullptr) {
        prev = current;
        if (value < current->value) {
            current = current->left;
        }
        else if (value > current->value) {
            current = current->right;
        }
        else {
            splay(current);
            return current;
        }
    }

    if (prev != nullptr) {
        splay(prev);
    }
    return nullptr;
}

SplayTree::Node* SplayTree::findMax(Node* node) {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) {
        node = node->right;
    }
    return node;
}

bool SplayTree::contains(int value) {
    Node* found = findNode(value);
    return found != nullptr;
}

bool SplayTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        tree_size = 1;
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        }
        else if (value > current->value) {
            current = current->right;
        }
        else {
            splay(current);
            return false;
        }
    }

    Node* newNode = new Node(value);
    newNode->parent = parent;

    if (value < parent->value) {
        parent->left = newNode;
    }
    else {
        parent->right = newNode;
    }

    splay(newNode);
    tree_size++;
    return true;
}

bool SplayTree::remove(int value) {
    Node* node = findNode(value);
    if (node == nullptr) {
        return false;
    }

    Node* leftTree = node->left;
    Node* rightTree = node->right;

    if (leftTree != nullptr) {
        leftTree->parent = nullptr;
    }
    if (rightTree != nullptr) {
        rightTree->parent = nullptr;
    }

    delete node;
    tree_size--;

    if (leftTree == nullptr) {
        root = rightTree;
    }
    else {
        Node* maxNode = findMax(leftTree);
        splay(maxNode);

        maxNode->right = rightTree;
        if (rightTree != nullptr) {
            rightTree->parent = maxNode;
        }

        root = maxNode;
    }

    return true;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

void SplayTree::inorder(Node* node, std::vector<int>& vec) const {
    if (node == nullptr) return;
    inorder(node->left, vec);
    vec.push_back(node->value);
    inorder(node->right, vec);
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    inorder(root, result);
    return result;
}

void SplayTree::clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left);
    clear(node->right);
    delete node;
}
