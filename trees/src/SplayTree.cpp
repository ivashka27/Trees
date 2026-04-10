#include "SplayTree.hpp"

// Вспомогательные повороты
SplayTree::Node* SplayTree::rotate_right(Node* v) {
    Node* u = v->left;
    v->left = u->right;
    u->right = v;
    return u;
}

SplayTree::Node* SplayTree::rotate_left(Node* v) {
    Node* u = v->right;
    v->right = u->left;
    u->left = v;
    return u;
}

// Операция Splay: поднимает узел с value (или ближайший) в корень
SplayTree::Node* SplayTree::splay(Node* curr, int value) {
    if (!curr || curr->value == value) return curr;

    if (value < curr->value) {
        if (!curr->left) return curr;
        if (value < curr->left->value) {
            curr->left->left = splay(curr->left->left, value);
            curr = rotate_right(curr);
        } else if (value > curr->left->value) {
            curr->left->right = splay(curr->left->right, value);
            if (curr->left->right) curr->left = rotate_left(curr->left);
        }
        return (curr->left == nullptr) ? curr : rotate_right(curr);
    } else {
        if (!curr->right) return curr;
        if (value < curr->right->value) {
            curr->right->left = splay(curr->right->left, value);
            if (curr->right->left) curr->right = rotate_right(curr->right);
        } else if (value > curr->right->value) {
            curr->right->right = splay(curr->right->right, value);
            curr = rotate_left(curr);
        }
        return (curr->right == nullptr) ? curr : rotate_left(curr);
    }
}

bool SplayTree::contains(int value) {
    if (!root) return false;
    root = splay(root, value);
    return root->value == value;
}

bool SplayTree::insert(int value) {
    if (!root) {
        root = new Node(value);
        tree_size++;
        return true;
    }
    root = splay(root, value);
    if (root->value == value) return false;

    Node* newNode = new Node(value);
    if (value < root->value) {
        newNode->right = root;
        newNode->left = root->left;
        root->left = nullptr;
    } else {
        newNode->left = root;
        newNode->right = root->right;
        root->right = nullptr;
    }
    root = newNode;
    tree_size++;
    return true;
}

bool SplayTree::remove(int value) {
    if (!root) return false;
    root = splay(root, value);
    if (root->value != value) return false;

    Node* oldRoot = root;
    if (!root->left) {
        root = root->right;
    } else {
        Node* leftSubtree = root->left;
        leftSubtree = splay(leftSubtree, value);
        leftSubtree->right = root->right;
        root = leftSubtree;
    }
    delete oldRoot;
    tree_size--;
    return true;
}

std::size_t SplayTree::size() const { return tree_size; }
bool SplayTree::empty() const { return tree_size == 0; }

void SplayTree::collect_values(Node* node, std::vector<int>& res) const {
    if (!node) return;
    collect_values(node->left, res);
    res.push_back(node->value);
    collect_values(node->right, res);
}

std::vector<int> SplayTree::values() const {
    std::vector<int> res;
    collect_values(root, res);
    return res;
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
