#pragma once

#include <cstddef>
#include <vector>

class Treap
{
private:
    struct Node
    {
        int key;
        int priority;
        Node* left;
        Node* right;

        Node(int value, int pr);
    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;

    static Node* merge(Node* left, Node* right);
    static void  split(Node* current, int value, Node*& left, Node*& right);
    static Node* insert_node(Node* current, Node* node);
    static Node* remove_node(Node* current, int value, bool& removed);
    static bool  contains_node(Node* current, int value);
    static void  inorder(Node* current, std::vector<int>& result);
    static void  destroy(Node* current);

public:
    Treap() = default;
    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;
    Treap(Treap&&) = delete;
    Treap& operator=(Treap&&) = delete;

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();
};