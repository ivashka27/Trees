#include "../include/treap.hpp"
#include <cstdlib>
#include <ctime>

Treap::Node::Node(int val):
    value(val),
    priority(std::rand()),
    left(nullptr),
    right(nullptr)
{
}

void Treap::split(Node* t, int key, Node*& left, Node*& right) {
    if (t == nullptr) {
        left = right = nullptr;
        return;
    } 
    else {
        if (key < t->value) {
            right = t;
            split(t->left, key, left, t->left);
        }
        else {
            left = t;
            split(t->right, key, t->right, right);
        }
    }
}

Treap::Node* Treap::merge(Node* left, Node* right) {
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}

bool Treap::contains(Node* node, int value) const {
    while (node != nullptr) {
        if (value == node->value) {
            return true;
        }
        if (value < node->value) {
            node = node->left;   
        }
        else {
            node = node->right;
        }
    }
    return false;
}

bool Treap::contains(int value) const {
    return contains(root_, value);
}

bool Treap::insert(int value) {
    if (contains(value)) {
        return false;
    }
    Node *left = nullptr;
    Node *right = nullptr;
    split(root_, value, left, right);
    Node* newNode = new Node(value);
    root_ = merge(merge(left, newNode), right);
    size_++;
    return true;
}

bool Treap::remove(int value) {
    if (!contains(value)) return false;
    Node *left = nullptr;
    Node *midRight = nullptr;
    split(root_, value, left, midRight);
    Node *mid = nullptr;
    split(left, value - 1, left, mid);
    delete mid;
    mid = nullptr;
    root_ = merge(left, midRight);
    size_--;
    return true;
}

void Treap::collect(Node* node, std::vector<int>& result) const {
    if (!node) return;
    collect(node->left, result);
    result.push_back(node->value);
    collect(node->right, result);
}

std::size_t Treap::size() const {
    return size_;
}

bool Treap::empty() const {
    return size_ == 0;
}

std::vector<int> Treap::values() const {
    std::vector<int> result;
    collect(root_, result);
    return result;
}

void Treap::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

Treap::~Treap() {
    clear(root_);
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    return 0;
}