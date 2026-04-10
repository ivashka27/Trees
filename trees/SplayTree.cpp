#include "include/SplayTree.hpp"

bool SplayTree::contains(int value) const
{
    Node* current = root_;
    Node* last = nullptr;

    while (current != nullptr)
    {
        last = current;

        if (value < current->value)
        {
            current = current->left;
        }
        else if (value > current->value)
        {
            current = current->right;
        }
        else
        {
            splay(current);
            return true;
        }
    }

    if (last != nullptr)
    {
        splay(last);
    }

    return false;
}

bool SplayTree::insert(int value)
{
    if (root_ == nullptr)
    {
        root_ = new Node{value, nullptr, nullptr, nullptr};
        size_ = 1;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;

    while (current != nullptr)
    {
        parent = current;

        if (value < current->value)
        {
            current = current->left;
        }
        else if (value > current->value)
        {
            current = current->right;
        }
        else
        {
            splay(current);
            return false;
        }
    }

    Node* node = new Node{value, nullptr, nullptr, parent};

    if (value < parent->value)
    {
        parent->left = node;
    }
    else
    {
        parent->right = node;
    }

    splay(node);
    ++size_;
    return true;
}

bool SplayTree::remove(int value)
{
    if (!contains(value))
    {
        return false;
    }

    Node* node = root_;
    Node* left = node->left;
    Node* right = node->right;

    if (left != nullptr)
    {
        left->parent = nullptr;
    }

    if (right != nullptr)
    {
        right->parent = nullptr;
    }

    delete node;
    --size_;

    if (left == nullptr)
    {
        root_ = right;
        return true;
    }

    root_ = left;

    Node* maximum = left;
    while (maximum->right != nullptr)
    {
        maximum = maximum->right;
    }

    splay(maximum);
    root_->right = right;

    if (right != nullptr)
    {
        right->parent = root_;
    }

    return true;
}

std::size_t SplayTree::size() const
{
    return size_;
}

bool SplayTree::empty() const
{
    return size_ == 0;
}

std::vector<int> SplayTree::values() const
{
    std::vector<int> result;
    result.reserve(size_);
    collectValues(root_, result);
    return result;
}

SplayTree::~SplayTree()
{
    destroy(root_);
    root_ = nullptr;
    size_ = 0;
}

void SplayTree::rotateLeft(Node* node) const
{
    Node* right = node->right;
    Node* parent = node->parent;

    node->right = right->left;
    if (right->left != nullptr)
    {
        right->left->parent = node;
    }

    right->left = node;
    right->parent = parent;
    node->parent = right;

    if (parent == nullptr)
    {
        root_ = right;
    }
    else if (parent->left == node)
    {
        parent->left = right;
    }
    else
    {
        parent->right = right;
    }
}

void SplayTree::rotateRight(Node* node) const
{
    Node* left = node->left;
    Node* parent = node->parent;

    node->left = left->right;
    if (left->right != nullptr)
    {
        left->right->parent = node;
    }

    left->right = node;
    left->parent = parent;
    node->parent = left;

    if (parent == nullptr)
    {
        root_ = left;
    }
    else if (parent->left == node)
    {
        parent->left = left;
    }
    else
    {
        parent->right = left;
    }
}

void SplayTree::splay(Node* node) const
{
    while (node->parent != nullptr)
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;

        if (grandparent == nullptr)
        {
            if (parent->left == node)
            {
                rotateRight(parent);
            }
            else
            {
                rotateLeft(parent);
            }
        }
        else if (grandparent->left == parent && parent->left == node)
        {
            rotateRight(grandparent);
            rotateRight(parent);
        }
        else if (grandparent->right == parent && parent->right == node)
        {
            rotateLeft(grandparent);
            rotateLeft(parent);
        }
        else if (grandparent->left == parent && parent->right == node)
        {
            rotateLeft(parent);
            rotateRight(grandparent);
        }
        else
        {
            rotateRight(parent);
            rotateLeft(grandparent);
        }
    }
}

void SplayTree::destroy(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    destroy(node->left);
    destroy(node->right);
    delete node;
}

void SplayTree::collectValues(Node* node, std::vector<int>& result) const
{
    if (node == nullptr)
    {
        return;
    }

    collectValues(node->left, result);
    result.push_back(node->value);
    collectValues(node->right, result);
}
