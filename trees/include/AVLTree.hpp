#pragma once

#include <vector>

class AVLTree {
public:
    AVLTree();
    ~AVLTree();

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        int height;
        Node(int val) : value(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;
    std::size_t count;

    // Вспомогательные приватные методы
    int height(Node* node) const;
    int balanceFactor(Node* node) const;
    void updateHeight(Node* node);

    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    Node* balance(Node* node);

    Node* insert(Node* node, int value, bool& inserted);
    Node* remove(Node* node, int value, bool& removed);
    Node* findMin(Node* node) const;

    bool contains(Node* node, int value) const;
    void collectValues(Node* node, std::vector<int>& result) const;
    void clear(Node* node);
};