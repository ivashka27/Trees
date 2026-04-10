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
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        Node* parent;
    };

    mutable Node* root_ = nullptr;
    std::size_t size_ = 0;

    void rotateLeft(Node* node) const;
    void rotateRight(Node* node) const;
    void splay(Node* node) const;

    void destroy(Node* node);
    void collectValues(Node* node, std::vector<int>& result) const;
};
