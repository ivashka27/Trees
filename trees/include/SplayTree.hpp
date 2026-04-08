#pragma once

#include <vector>

class SplayTree
{
private:
    struct Node {
        Node* left;
        Node* right;
        Node* parent;
        int value;
    };

    mutable Node* root_ = nullptr; // splay перестраивает дерево, а `contains` объявлен как `const`
    std::size_t size_ = 0;

    Node* findNode(int value) const;
    Node* findLast(int value) const;
    void rotateLeft(Node* x) const;
    void rotateRight(Node* x) const;
    void splay(Node* x) const;

    void clear(Node* x);
    void inorder(Node* node, std::vector<int>& out) const;
    
    Node* subtreeMax(Node* node) const;
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();
};