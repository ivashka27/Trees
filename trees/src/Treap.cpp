#include "Treap.hpp"

void Treap::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

Treap::~Treap() {
    clear(root);
}

void Treap::split(Node* t, int key, Node*& l, Node*& r) {
    if (t == nullptr) {
        l = r = nullptr;
        return;
    }
    if (t-> value < key) {
        split(t->right, key, t->right, r);
        l = t;
    } else {
        split(t->left, key, l, t->left);
        r = t;
    }
}

Treap::Node* Treap::merge(Node* l, Node* r) {
    if (l == nullptr || r == nullptr) {
        return l != nullptr ? l : r;
    }
    if (l->priority > r->priority) {
        l->right = merge(l->right, r);
        return l;
    } else {
        r->left = merge(l, r->left);
        return r;
    }
}

bool Treap::contains(int value) const {
    Node* current = root;
    while (current != nullptr) {
        if (current->value == value) {
            return true;
        }
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

bool Treap::insert(int value) {
    if (contains(value)) {
        return false;
    }

    Node* l;
    Node* r;
    split(root, value, l, r);

    std::uniform_int_distribution<int> dist;
    Node* newNode = new Node(value, dist(rng));

    root = merge(merge(l, newNode), r);
    _size++;
    return true;
}

bool Treap::remove(int value) {
    if (!contains(value)) {
        return false;
    }

    Node* l;
    Node* r;
    Node* m;

    split(root, value, l, r);
    split(r, value + 1, m, r);

    delete m;

    root = merge(l, r);
    _size--;
    return true;
}

std::size_t Treap::size() const {
    return _size;
}

bool Treap::empty() const {
    return _size == 0;
}

void Treap::inorder(Node* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

std::vector<int> Treap::values() const {
    std::vector<int> result;
    result.reserve(_size);
    inorder(root, result);
    return result;
}