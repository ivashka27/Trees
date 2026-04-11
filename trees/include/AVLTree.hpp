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
    struct Node {
        int key;
        int height;
        Node* left;
        Node* right;

        Node(int k) : key(k), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    int height(Node* p) const;
    int balance_factor(Node* p) const;
    void fix_height(Node* p);
    
    Node* rotate_right(Node* p);
    Node* rotate_left(Node* q);
    Node* balance(Node* p);

    Node* insert(Node* p, int k, bool& inserted);
    Node* remove(Node* p, int k, bool& removed);
    Node* find_min(Node* p) const;
    Node* remove_min(Node* p);
    
    void clear(Node* p);
    void collect_values(Node* p, std::vector<int>& res) const;
};