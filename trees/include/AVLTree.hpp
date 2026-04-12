#pragma once

#include <vector>

class AVLTree
{
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;

        Node(int val)
            : value(val), height(0), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    int get_h(Node* node) const;
    void update_h(Node* node);
    int difference(Node* node) const;

    Node* rotate_left(Node* node);
    Node* rotate_right(Node* node);
    Node* balance(Node* node);

    Node* insert(Node* node, int val);
    Node* remove(Node* node, int val);
    Node* min_val(Node* node) const;

    void in_order(Node* node, std::vector<int>& values) const;
    void clear(Node* node);

public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();
};
