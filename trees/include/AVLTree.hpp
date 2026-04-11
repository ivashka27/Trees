#pragma once

#include <vector>

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
    struct Node;

    Node * root_ = nullptr;

    std::size_t size_ = 0;

    static int get_height(const Node* node);
    static void update_height(Node* node);
    static Node * rotate_left(Node* node);
    static Node * rotate_right(Node* node);
    static int get_balance(Node* node);
    static Node * rebalance(Node* node);
    static Node * insert_node(Node* node, const int value, bool & inserted);
    static Node * remove_node(Node* node, const int value, bool & removed);
    static Node * get_max(Node* node);
    static bool contains_node(const Node* node, int value);
    static void inorder(const Node* node, std::vector<int> & result);
    static void clear_tree(Node* node);
};