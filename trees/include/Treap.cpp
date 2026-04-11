#include "Treap.hpp"
#include <random>
#include <algorithm>


std::pair<Treap::Node*, Treap::Node*> Treap::split(Node* t, int key) {
    if (!t) return {nullptr, nullptr};
    if (t->key <= key) {
        auto [L, R] = split(t->right, key);
        t->right = L;
        return {t, R};
    } else {
        auto [L, R] = split(t->left, key);
        t->left = R;
        return {L, t};
    }
}

Treap::Node* Treap::merge(Node* L, Node* R) {
    if (!L || !R) return L ? L : R;
    if (L->priority > R->priority) {
        L->right = merge(L->right, R);
        return L;
    } else {
        R->left = merge(L, R->left);
        return R;
    }
}


bool Treap::insert(int value) {
    if (contains(value)) return false;
    
    int priority = std::rand(); 
    auto [L, R] = split(root, value);
    root = merge(merge(L, new Node(value, priority)), R);
    tree_size++;
    return true;
}

void Treap::collectValues(Node* t, std::vector<int>& res) const{
    if (!t) return;
    collectValues(t->left, res);
    res.push_back(t->key);
    collectValues(t->right, res);
}

bool Treap::contains(int value) const {
    Node* curr = root;
    while (curr) {
        if (curr->key == value) return true;
        curr = (value < curr->key) ? curr->left : curr->right;
    }
    return false;
}

bool Treap::remove(int value) {
    if (!contains(value)) return false;
    auto [L, R] = split(root, value);
    auto [L_actual, M] = split(L, value - 1);
    clear(M); 
    root = merge(L_actual, R);
    tree_size--;
    return true;
}
std::size_t Treap::size() const {
    return tree_size;
}
bool Treap::empty() const {
    return tree_size == 0;
}
std::vector<int> Treap::values() const {
    std::vector<int> res;
    res.reserve(tree_size);
    collectValues(root, res);
    return res;
}

Treap::~Treap() {
    clear(root);
}
void Treap::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node; 
}