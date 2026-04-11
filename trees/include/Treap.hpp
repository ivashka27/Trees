#pragma once

#include <vector>
#include <cstddef>
#include <random>

class Treap
{
private:
    struct Node {
        int value;
        int priority;
        Node* left;
        Node* right;

        Node(int val, int prio) : value(val), priority(prio), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t _size = 0;

    std::mt19937 rng{std::random_device{}()};

    void split(Node* t, int key, Node*& l, Node*& r);
    Node* merge(Node* l, Node* r);
    void clear(Node* node);
    void inorder(Node* node, std::vector<int>& result) const;

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();
};