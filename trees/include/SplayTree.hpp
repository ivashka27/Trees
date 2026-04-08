#pragma once

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
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;
        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t treeSize = 0;

    void rotate(Node* x);
    void splay(Node* x);
    Node* find(int value) const;
    Node* findMax(Node* node) const;
    Node* findMin(Node* node) const;
    void split(Node*& t, int key, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);
    void clear(Node* node);
    void inorder(Node* node, std::vector<int>& result) const;
};
