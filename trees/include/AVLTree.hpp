#pragma once

#include <vector>
#include <cstddef>
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
    struct Node {
        int key;
        int height;
        Node *left;
        Node *right;

        Node(int k) : key(k), height(0), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    int height(Node* p) const;
    void fixheight(Node* p);
    int bfactor(Node* p) const;
    
    Node* rotateRight(Node* p);
    Node* rotateLeft(Node* q);
    Node* balance(Node* p);

    Node* insert(Node* p, int k, bool& inserted);
    Node* remove(Node* p, int k, bool& removed);
    
    Node* findMin(Node* p) const;
    Node* removeMin(Node* p);
    
    void clear(Node* p);
    void collectValues(Node* p, std::vector<int>& v) const;
};