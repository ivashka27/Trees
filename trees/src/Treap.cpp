#include "../include/Treap.hpp"
#include <cstdlib>
#include <ctime>

Treap::Node::Node(int value, int pr)
    : key(value), priority(pr), left(nullptr), right(nullptr)
{
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

void Treap::split(Node* current, int value, Node*& left, Node*& right)
{
    if (current == nullptr)
    {
        left = nullptr;
        right = nullptr;
        return;
    }

    if (current->key < value)
    {
        split(current->right, value, current->right, right);
        left = current;
    }
    else
    {
        split(current->left, value, left, current->left);
        right = current;
    }
}

Treap::Node* Treap::insert_node(Node* current, Node* node)
{
    if (current == nullptr)
    {
        return node;
    }

    if (node->priority > current->priority)
    {
        split(current, node->key, node->left, node->right);
        return node;
    }

    if (node->key < current->key)
    {
        current->left = insert_node(current->left, node);
    }
    else
    {
        current->right = insert_node(current->right, node);
    }

    return current;
}

Treap::Node* Treap::remove_node(Node* current, int value, bool& removed)
{
    if (current == nullptr)
    {
        return nullptr;
    }

    if (value < current->key)
    {
        current->left = remove_node(current->left, value, removed);
        return current;
    }

    if (value > current->key)
    {
        current->right = remove_node(current->right, value, removed);
        return current;
    }

    Node* result = merge(current->left, current->right);
    delete current;
    removed = true;
    return result;
}

bool Treap::contains_node(Node* current, int value)
{
    while (current != nullptr)
    {
        if (value == current->key)
        {
            return true;
        }

        if (value < current->key)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    return false;
}

void Treap::inorder(Node* current, std::vector<int>& result)
{
    if (current == nullptr)
    {
        return;
    }

    inorder(current->left, result);
    result.push_back(current->key);
    inorder(current->right, result);
}

void Treap::destroy(Node* current)
{
    if (current == nullptr)
    {
        return;
    }

    destroy(current->left);
    destroy(current->right);
    delete current;
}

bool Treap::contains(int value) const
{
    return contains_node(root_, value);
}

bool Treap::insert(int value)
{
    if (contains(value))
    {
        return false;
    }

    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        seeded = true;
    }

    Node* node = new Node(value, std::rand());
    root_ = insert_node(root_, node);
    ++size_;
    return true;
}

bool Treap::remove(int value)
{
    bool removed = false;
    root_ = remove_node(root_, value, removed);

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
    inorder(root_, result);
    return result;
}

Treap::~Treap()
{
    destroy(root_);
}