#include "AVLTree.hpp"
#include <algorithm>

int AVLTree::getHeight(Node* node) const
{
    return node ? node->height : -1;
}

int AVLTree::getBalance(Node* node) const
{
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVLTree::updateHeight(Node* node)
{
    if (node)
    {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* node)
{
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

AVLTree::Node* AVLTree::rotateLeft(Node* node)
{
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;

    updateHeight(node);
    updateHeight(newRoot);

    return newRoot;
}

AVLTree::Node* AVLTree::balance(Node* node)
{
    updateHeight(node);
    int balance = getBalance(node);

    if (balance > 1)
    {
        if (getBalance(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }

    if (balance < -1)
    {
        if (getBalance(node->right) > 0)
        {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }

    return node;
}

AVLTree::Node* AVLTree::insert(Node* node, int value, bool& inserted)
{
    if (!node)
    {
        inserted = true;
        return new Node(value);
    }

    if (value < node->value)
    {
        node->left = insert(node->left, value, inserted);
    }
    else if (value > node->value)
    {
        node->right = insert(node->right, value, inserted);
    }

    return balance(node);
}

bool AVLTree::insert(int value)
{
    bool inserted = false;
    root_ = insert(root_, value, inserted);
    if (inserted)
    {
        ++size_;
    }
    return inserted;
}

AVLTree::Node* AVLTree::findMin(Node* node) const
{
    while (node && node->left)
    {
        node = node->left;
    }
    return node;
}

AVLTree::Node* AVLTree::removeMin(Node* node)
{
    if (!node->left)
    {
        Node* right = node->right;
        delete node;
        return right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

AVLTree::Node* AVLTree::remove(Node* node, int value, bool& removed)
{
    if (!node)
    {
        return nullptr;
    }

    if (value < node->value)
    {
        node->left = remove(node->left, value, removed);
    }
    else if (value > node->value)
    {
        node->right = remove(node->right, value, removed);
    }
    else
    {
        removed = true;

        if (!node->left && !node->right)
        {
            delete node;
            return nullptr;
        }
        else if (!node->left)
        {
            Node* right = node->right;
            delete node;
            return right;
        }
        else if (!node->right)
        {
            Node* left = node->left;
            delete node;
            return left;
        }
        else
        {
            Node* minNode = findMin(node->right);
            node->value = minNode->value;
            node->right = removeMin(node->right);
        }
    }

    return balance(node);
}

bool AVLTree::remove(int value)
{
    bool removed = false;
    root_ = remove(root_, value, removed);
    if (removed)
    {
        --size_;
    }
    return removed;
}

bool AVLTree::contains(Node* node, int value) const
{
    if (!node)
    {
        return false;
    }
    if (value == node->value)
    {
        return true;
    }
    if (value < node->value)
    {
        return contains(node->left, value);
    }
    return contains(node->right, value);
}

bool AVLTree::contains(int value) const
{
    return contains(root_, value);
}

std::size_t AVLTree::size() const
{
    return size_;
}

bool AVLTree::empty() const
{
    return size_ == 0;
}
void AVLTree::inorder(Node* node, std::vector<int>& result) const
{
    if (!node)
    {
        return;
    }
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

std::vector<int> AVLTree::values() const
{
    std::vector<int> result;
    result.reserve(size_);
    inorder(root_, result);
    return result;
}

void AVLTree::destroy(Node* node)
{
    if (!node)
    {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}

AVLTree::~AVLTree()
{
    destroy(root_);
}
