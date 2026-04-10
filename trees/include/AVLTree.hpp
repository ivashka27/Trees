#pragma once

#include <vector>
#include <algorithm>
#include <cstddef>

class AVLTree {
private:
    struct Node {
        int value;
        Node *left, *right;
        int height;
        Node(int val) : value(val), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root = nullptr;
    std::size_t _size = 0;

    void destroy(Node* node);
    int getHeight(Node* node);
    void updateHeight(Node* node);
    int getBalance(Node* node);
    
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    Node* insertInternal(Node* node, int value, bool& success);
    Node* removeInternal(Node* node, int value, bool& success);
    void inOrder(Node* node, std::vector<int>& vec) const;
    Node* findMin(Node* node);
    Node* removeMin(Node* node);

public:
    AVLTree() = default;
    ~AVLTree();

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;
};
