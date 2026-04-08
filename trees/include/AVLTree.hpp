#pragma once

#include <vector>
#include <algorithm>

class AVLTree
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;
    std::vector<int> values() const;

    ~AVLTree();

private:
    struct Node
    {
        int key;
        Node* left;
        Node* right;
        int height;

        Node(int value);
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    int get_height(Node* node) const;
    int update_height(Node* node);

    int get_balance(Node* node) const;

    Node* right_rotate(Node* node);
    Node* left_rotate(Node* node);

    Node* balance(Node* node);

    Node* insert_node(Node* node, int value);
    Node* remove_node(Node* node, int value);

    Node* find_min(Node* node) const;
    void in_order(Node* node, std::vector<int>& result) const;
    void destroy(Node* node);
};