#include "Treap.hpp"
#include <cstdlib>
#include <ctime>


Treap::Node::Node(int val)
    : value(val)
    , priority(std::rand())
    , left(nullptr)
    , right(nullptr)
{
}


Treap::Treap()
    : root(nullptr)
    , tree_size(0)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

bool Treap::contains(int value) const
{
    return find(root, value) != nullptr;
}

bool Treap::insert(int value)
{
    if (contains(value)) {
        return false;
    }

    auto [left, right] = split(root, value);
    Node* new_node = new Node(value);
    root = merge(merge(left, new_node), right);
    ++tree_size;
    return true;
}

bool Treap::remove(int value)
{
    if (!contains(value)) {
        return false;
    }

    auto [left, mid] = split(root, value - 1);
    auto [to_delete, right] = split(mid, value);
    delete to_delete;
    root = merge(left, right);
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
    collect_values(root, result);
    return result;
}

Treap::~Treap()
{
    delete_subtree(root);
}


Treap::Node* Treap::merge(Node* left, Node* right)
{
    if (!left) return right;
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

std::pair<Treap::Node*, Treap::Node*> Treap::split(Node* node, int key)
{
    if (!node) {
        return { nullptr, nullptr };
    }

    if (node->value <= key) {
        auto [left, right] = split(node->right, key);
        node->right = left;
        return { node, right };
    }
    else {
        auto [left, right] = split(node->left, key);
        node->left = right;
        return { left, node };
    }
}

Treap::Node* Treap::find(Node* node, int value) const
{
    if (!node) return nullptr;

    if (value == node->value) {
        return node;
    }
    else if (value < node->value) {
        return find(node->left, value);
    }
    else {
        return find(node->right, value);
    }
}

void Treap::collect_values(Node* node, std::vector<int>& result) const
{
    if (!node) return;

    collect_values(node->left, result);
    result.push_back(node->value);
    collect_values(node->right, result);
}

void Treap::delete_subtree(Node* node)
{
    if (!node) return;

    delete_subtree(node->left);
    delete_subtree(node->right);
    delete node;
}