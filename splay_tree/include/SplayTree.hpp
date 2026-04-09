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

        Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void splay(Node* x);

    Node* find(int value) const;
    void deleteSubtree(Node* node);
    void inorder(Node* node, std::vector<int>& result) const;
};
