#pragma once

#include <vector>
#include <cstddef>

class SplayTree
{
public:
    bool contains(int value); // Splay меняет дерево, поэтому не const
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();

private:
    struct Node {
        int value;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int val) : value(val) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    // Внутренние методы
    Node* splay(Node* node, int value);
    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
    void clear(Node* node);
    void collect_values(Node* node, std::vector<int>& res) const;
};
