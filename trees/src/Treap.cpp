#include "Treap.hpp"
#include <cstdlib>   // rand()
#include <climits>

struct Node {
    int value;
    int priority;
    Node* left  = nullptr;
    Node* right = nullptr;

    explicit Node(int v) :value(v), priority(rand()) {}
};

static void destroyTree(Node* node) {
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

static void split(Node* node, int key, Node*& left, Node*& right) {
    if (!node) {
        left = right = nullptr;
        return;
    }
    if (node->value <= key) {
        // узел уходит в левую часть; правое поддерево делим дальше
        split(node->right, key, node->right, right);
        left = node;
    }
    else {
        // узел уходит в правую часть; левое поддерево делим дальше
        split(node->left, key, left, node->left);
        right = node;
    }
}

static Node* merge(Node* left, Node* right) {
    if (!left)  return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

static void inorder(Node* node, std::vector<int>& out) {
    if (!node) return;
    inorder(node->left, out);
    out.push_back(node->value);
    inorder(node->right, out);
}

struct TreapImpl {
    Node*       root = nullptr;
    std::size_t sz   = 0;
};

bool Treap::contains(int value) const {
    Node* cur = root_;
    while (cur) {
        if      (value < cur->value) {
            cur = cur->left;
        }
        else if (value > cur->value) {
            cur = cur->right;
        }
        else {
            return true;
        }
    }
    return false;
}

bool Treap::insert(int value) {
    if (contains(value)) {
    return false;
    }

    Node* left  = nullptr;
    Node* right = nullptr;
    split(root_, value, left, right);

    Node* newNode = new Node(value);
    root_ = merge(merge(left, newNode), right);
    ++sz_;
    return true;
}

bool Treap::remove(int value) {
    if (!contains(value)) return false;

    Node* left = nullptr;
    Node* mid = nullptr;
    Node* right = nullptr;

    split(root_, value - 1, left, mid);
    split(mid, value, mid, right);
    
    delete mid;
    root_ = merge(left, right);
    --sz_;
    return true;
}

std::size_t Treap::size() const  {return sz_;}
bool Treap::empty() const {return sz_ == 0;}

std::vector<int> Treap::values() const {
    std::vector<int> result;
    result.reserve(sz_);
    inorder(root_, result);
    return result;
}

Treap::~Treap() {
    destroyTree(root_);
}