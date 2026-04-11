#include "SplayTree.hpp"
#include <climits>


SplayTree::SplayTree() : root(nullptr), tree_size(0) {}

SplayTree::Node::Node(int v)
        : value(v), left(nullptr), right(nullptr) {}


void SplayTree::rotateRight(Node*& t) {
    Node* x = t->left;
    t->left = x->right;
    x->right = t;
    t = x;
}

void SplayTree::rotateLeft(Node*& t) {
    Node* x = t->right;
    t->right = x->left;
    x->left = t;
    t = x;
}


void SplayTree::splay(Node*& t, int value) {
    if (!t) return;

    if (value < t->value) {
        if (!t->left) return;

        if (value < t->left->value) {
            splay(t->left->left, value);
            rotateRight(t);
        } else if (value > t->left->value) {
            splay(t->left->right, value);
            if (t->left->right)
                rotateLeft(t->left);
        }

        if (t->left)
            rotateRight(t);
    }
    else if (value > t->value) {
        if (!t->right) return;

        if (value > t->right->value) {
            splay(t->right->right, value);
            rotateLeft(t);
        } else if (value < t->right->value) {
            splay(t->right->left, value);
            if (t->right->left)
                rotateRight(t->right);
        }

        if (t->right)
            rotateLeft(t);
    }
}


std::pair<SplayTree::Node*, SplayTree::Node*>
SplayTree::split(Node* t, int value) {
    if (!t) return {nullptr, nullptr};

    splay(t, value);

    if (t->value < value) {
        Node* right = t->right;
        t->right = nullptr;
        return {t, right};
    } else {
        Node* left = t->left;
        t->left = nullptr;
        return {left, t};
    }
}

SplayTree::Node* SplayTree::merge(Node* left, Node* right) {
    if (!left) return right;
    if (!right) return left;

    splay(left, INT_MAX);
    left->right = right;
    return left;
}


bool SplayTree::contains(int value) const {
    if (!root) return false;

    Node*& r = const_cast<Node*&>(root);
    const_cast<SplayTree*>(this)->splay(r, value);

    return root && root->value == value;
}

bool SplayTree::insert(int value) {
    auto [l, r] = split(root, value);

    if (r && r->value == value) {
        root = merge(l, r);
        return false;
    }

    Node* node = new Node(value);
    node->left = l;
    node->right = r;

    root = node;
    tree_size++;
    return true;
}

bool SplayTree::remove(int value) {
    if (!root) return false;

    splay(root, value);

    if (!root || root->value != value)
        return false;

    Node* left = root->left;
    Node* right = root->right;

    delete root;
    tree_size--;

    root = merge(left, right);
    return true;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

std::vector<int> SplayTree::values() const {
    std::vector<int> res;
    inorder(root, res);
    return res;
}


void SplayTree::inorder(Node* t, std::vector<int>& res) const {
    if (!t) return;
    inorder(t->left, res);
    res.push_back(t->value);
    inorder(t->right, res);
}

void SplayTree::clear(Node* t) {
    if (!t) return;
    clear(t->left);
    clear(t->right);
    delete t;
}


SplayTree::~SplayTree() {
    clear(root);
}