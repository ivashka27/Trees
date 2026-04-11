#pragma once

#include <vector>
#include <cstddef>

class SplayTree {
private:
    struct Node {
        int key;
        Node* left;
        Node* right;
        Node* parent;

        Node(int k, Node* p = nullptr) 
            : key(k), left(nullptr), right(nullptr), parent(p) {}
    };

    mutable Node* root;
    std::size_t tree_size;

    void rotateLeft(Node* x) const;
    void rotateRight(Node* x) const;
    void splay(Node* x) const;
    Node* findNode(int value) const;
    Node* getMaximum(Node* node) const;
    void destroySubtree(Node* node);
    void inorderTraversal(Node* node, std::vector<int>& result) const;

public:
    SplayTree();
    ~SplayTree();
    
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);
    
    std::size_t size() const;
    bool empty() const;
    
    std::vector<int> values() const;
    
    void clear();

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;
};
