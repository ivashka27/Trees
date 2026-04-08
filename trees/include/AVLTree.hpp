#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

struct Node
{

    Node *left_node;
    Node *right_node;
    int height;
    int value;

    Node(int val);

    // forbid copy, move
    Node(const Node &other) = delete;
    Node &operator=(const Node &other) = delete;
    Node(Node &&other) = delete;
    Node &operator=(Node &&other) = delete;

    ~Node();
};

class AVLTree
{
private:
    friend int main(); // сделал так, чтобы не добавлять конструктор по умолчанию в поле public, где должны находиться только определенные методы.

    AVLTree() = default;

    Node *leftRotate(Node *x_node);
    Node *rightRotate(Node *x_node);
    Node *left_rightRotate(Node *x_node);
    Node *right_leftRotate(Node *x_node);
    Node *balance(Node *node);

    std::size_t size(Node *node) const;
    std::size_t update_height(Node *node) const;

    Node *contains(int value, Node *node) const;
    Node *insert(int value, Node *node);
    int getHeight(Node *node) const;
    int balance_factor(Node *node) const;
    void values(Node *node, std::vector<int> &vec) const;
    Node *find_min_Node(Node *node);
    Node *remove(int value, Node *node);


    // foibid copy, move
    AVLTree(const AVLTree &other);
    AVLTree &operator=(const AVLTree &other);
    AVLTree(AVLTree &&other);
    AVLTree &operator=(AVLTree &&other);

    Node *root_Node_ = nullptr;
public:

    bool contains(int value) const;

    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;

    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();
};
