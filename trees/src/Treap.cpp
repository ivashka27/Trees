#include "Treap.hpp"

#include <cstdlib>
#include <vector>

Treap::Node::Node(int value, int pr)
    : key(value), priority(pr), left(nullptr), right(nullptr)
{
}

Treap::Node* Treap::merge(Node* left, Node* right)
{
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

    right->left = merge(left, right->left);
    return right;
}

void Treap::split(Node* current, int value, Node*& left, Node*& right)
{
    if (current == nullptr) {
        left = nullptr;
        right = nullptr;
        return;
    }

    if (current->key < value) {
        split(current->right, value, current->right, right);
        left = current;
    } else {
        split(current->left, value, left, current->left);
        right = current;
    }
}

Treap::Node* Treap::insertNode(Node* current, Node* node)
{
    if (current == nullptr) {
        return node;
    }

    if (node->priority > current->priority) {
        split(current, node->key, node->left, node->right);
        return node;
    }

    if (node->key < current->key) {
        current->left = insertNode(current->left, node);
    } else {
        current->right = insertNode(current->right, node);
    }

    return current;
}

Treap::Node* Treap::removeNode(Node* current, int value)
{
    if (current == nullptr) {
        return nullptr;
    }

    if (value < current->key) {
        current->left = removeNode(current->left, value);
        return current;
    }

    if (value > current->key) {
        current->right = removeNode(current->right, value);
        return current;
    }

    Node* result = merge(current->left, current->right);
    delete current;
    return result;
}

bool Treap::containsNode(Node* current, int value)
{
    while (current != nullptr) {
        if (value == current->key) {
            return true;
        }

        if (value < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return false;
}

void Treap::inorder(Node* current, std::vector<int>& result)
{
    if (current == nullptr) {
        return;
    }

    inorder(current->left, result);
    result.push_back(current->key);
    inorder(current->right, result);
}

void Treap::destroy(Node* current)
{
    if (current == nullptr) {
        return;
    }

    destroy(current->left);
    destroy(current->right);
    delete current;
}

bool Treap::contains(int value) const
{
    return containsNode(root, value);
}

bool Treap::insert(int value)
{
    if (contains(value)) {
        return false;
    }

    Node* node = new Node(value, std::rand());
    root = insertNode(root, node);
    ++tree_size;
    return true;
}

bool Treap::remove(int value)
{
    if (!contains(value)) {
        return false;
    }

    root = removeNode(root, value);
    --tree_size;
    return true;
}

std::size_t Treap::size() const
{
    return tree_size;
}

bool Treap::empty() const
{
    return tree_size == 0;
}

std::vector<int> Treap::values() const
{
    std::vector<int> result;
    result.reserve(tree_size);
    inorder(root, result);
    return result;
}

Treap::~Treap()
{
    destroy(root);
}
