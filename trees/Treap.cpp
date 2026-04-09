#include "include/Treap.hpp"

#include <cstdlib>
#include <ctime>

Treap::Node::Node(int value, int priority)
    : value(value), priority(priority), left(nullptr), right(nullptr)
{
}

bool Treap::contains(int value) const
{
    return contains(root_, value);
}

bool Treap::insert(int value)
{
    if (contains(value))
    {
        return false;
    }

    static bool random_initialized = false;
    if (!random_initialized)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        random_initialized = true;
    }

    Node* new_node = new Node(value, std::rand());
    root_ = insert(root_, new_node);
    ++size_;
    return true;
}

bool Treap::remove(int value)
{
    bool removed = false;
    root_ = remove(root_, value, removed);
    if (removed)
    {
        --size_;
    }
    return removed;
}

std::size_t Treap::size() const
{
    return size_;
}

bool Treap::empty() const
{
    return size_ == 0;
}

std::vector<int> Treap::values() const
{
    std::vector<int> result;
    result.reserve(size_);
    collect_values(root_, result);
    return result;
}

Treap::~Treap()
{
    destroy(root_);
}

bool Treap::contains(Node* node, int value) const
{
    while (node != nullptr)
    {
        if (value == node->value)
        {
            return true;
        }

        if (value < node->value)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }

    return false;
}

void Treap::collect_values(Node* node, std::vector<int>& result) const
{
    if (node == nullptr)
    {
        return;
    }

    collect_values(node->left, result);
    result.push_back(node->value);
    collect_values(node->right, result);
}

void Treap::destroy(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void Treap::split(Node* node, int value, Node*& left, Node*& right)
{
    if (node == nullptr)
    {
        left = nullptr;
        right = nullptr;
        return;
    }

    if (node->value < value)
    {
        split(node->right, value, node->right, right);
        left = node;
    }
    else
    {
        split(node->left, value, left, node->left);
        right = node;
    }
}

Treap::Node* Treap::merge(Node* left, Node* right)
{
    if (left == nullptr)
    {
        return right;
    }

    if (right == nullptr)
    {
        return left;
    }

    if (left->priority > right->priority)
    {
        left->right = merge(left->right, right);
        return left;
    }

    right->left = merge(left, right->left);
    return right;
}

Treap::Node* Treap::insert(Node* node, Node* new_node)
{
    if (node == nullptr)
    {
        return new_node;
    }

    if (new_node->priority > node->priority)
    {
        split(node, new_node->value, new_node->left, new_node->right);
        return new_node;
    }

    if (new_node->value < node->value)
    {
        node->left = insert(node->left, new_node);
    }
    else
    {
        node->right = insert(node->right, new_node);
    }

    return node;
}

Treap::Node* Treap::remove(Node* node, int value, bool& removed)
{
    if (node == nullptr)
    {
        return nullptr;
    }

    if (value < node->value)
    {
        node->left = remove(node->left, value, removed);
        return node;
    }

    if (value > node->value)
    {
        node->right = remove(node->right, value, removed);
        return node;
    }

    removed = true;
    Node* merged = merge(node->left, node->right);
    delete node;
    return merged;
}
