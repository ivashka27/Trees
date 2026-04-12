#pragma once

#include <vector>
#include <cstddef>

class AVLTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        int height;
        
        Node(int val) : value(val), left(nullptr), right(nullptr), height(0) {}
    };
    
    Node* root;
    std::size_t tree_size;
    
    // Вспомогательные методы
    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);
    
    // Вращения
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    Node* balance(Node* node);
    
    // Основные операции
    Node* insertNode(Node* node, int value, bool& inserted);
    Node* removeNode(Node* node, int value, bool& removed);
    Node* findMin(Node* node) const;
    Node* removeMin(Node* node);
    
    bool containsNode(Node* node, int value) const;
    void collectValues(Node* node, std::vector<int>& result) const;
    void deleteTree(Node* node);
    
public:
    AVLTree();
    ~AVLTree();
    
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);
    
    std::size_t size() const;
    bool empty() const;
    
    std::vector<int> values() const;
};
