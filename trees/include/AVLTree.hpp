#pragma once
#include <vector>
#include <cstddef>
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
    struct Node{
        int value;
        int height;
        Node* left;
        Node* right;
        Node(int v) : value(v), height(0), left(nullptr), right(nullptr) {};
    };

    Node* root = nullptr;
    std::size_t _size = 0;

    int getHeight(Node* n) const;
    void updateHeight(Node* n);
    int getBalance(Node* n) const;

    Node* rotateLeft(Node* a);
    Node* rotateRight(Node* a);
    Node* bigRotateLeft(Node* a);
    Node* bigRotateRight(Node* a);

    bool contains(Node* node, int value) const;
    Node* insert(Node* node, int value);
    Node* remove(Node* node, int value);
    Node* findMin(Node* node) const;

    void inorderTraversal(Node* node, std::vector<int>& result) const;
    void clear(Node* node);

};