#pragma once

#include <vector>
#include <cstddef>
#include <utility>

class SplayTree
{
public:
    SplayTree();

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

        Node(int v);
    };

    Node* root;
    std::size_t tree_size;

    void splay(Node*& t, int value);
    void rotateLeft(Node*& t);
    void rotateRight(Node*& t);

    std::pair<Node*, Node*> split(Node* t, int value);
    Node* merge(Node* left, Node* right);

    void clear(Node* t);
    void inorder(Node* t, std::vector<int>& res) const;
};