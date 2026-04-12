#pragma once

#include <cstddef>
#include <vector>

class SplayTree
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();

private:
    struct Node;

    static Node* rotateRight(Node* node);
    static Node* rotateLeft(Node* node);
    static Node* splay(Node* node, int value);
    static void inorder(const Node* node, std::vector<int>& result);
    static void clear(Node* node);

    mutable Node* root_ = nullptr;
    std::size_t size_ = 0;
};
