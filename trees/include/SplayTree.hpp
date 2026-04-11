#pragma once

#include <vector>
#include <cstddef>

class SplayTree
{
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    mutable Node* root = nullptr; 
    std::size_t node_count = 0;

    void leftRotate(Node* x) const;
    void rightRotate(Node* x) const;
    void splay(Node* x) const;
    
    void destroyTree(Node* node);
    void inOrderTraversal(Node* node, std::vector<int>& result) const;

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();
};