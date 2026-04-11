#pragma once

#include <cstddef>
#include <vector>
#include <utility>

class Treap
{
private:
    struct Node {
        int key;
        int priority;
        Node *left = nullptr;
        Node *right = nullptr;
        Node(int k, int p) : key(k), priority(p) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;
    void clear(Node* node);
    std::pair<Node*, Node*> split(Node* t, int key);
    Node* merge(Node* L, Node* R);
    void collectValues(Node* node, std::vector<int>& res) const;

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();
};