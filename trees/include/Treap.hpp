#pragma once

#include <cstddef>
#include <vector>

class Treap
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();

private:
    struct Node
    {
        int value;
        int priority;
        Node* left;
        Node* right;

        Node(int value, int priority);
    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;

    bool contains(Node* node, int value) const;
    void collect_values(Node* node, std::vector<int>& result) const;
    void destroy(Node* node);

    void split(Node* node, int value, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);
    Node* insert(Node* node, Node* new_node);
    Node* remove(Node* node, int value, bool& removed);
};
