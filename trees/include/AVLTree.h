#pragma once

#include <vector>
#include <cstddef>

class AVLTree
{
    public:
        AVLTree() = default;

        bool contains(int value) const;
        bool insert(int value);
        bool remove(int value);

        std::size_t size() const;
        bool empty() const;

        std::vector<int> values() const;

        ~AVLTree();

    private:
        struct Node;

        Node* root = nullptr;
        std::size_t sz = 0;

        int height(Node* node) const;
        void updateHeight(Node* node);
        int balanceFactor(Node* node) const;

        Node* rotateLeft(Node* x);
        Node* rotateRight(Node* y);
        Node* balance(Node* node);

        Node* insertNode(Node* node, int value, bool& inserted);
        Node* removeNode(Node* node, int value, bool& removed);

        Node* findMin(Node* node) const;
        Node* removeMin(Node* node);

        bool containsNode(Node* node, int value) const;
        void inorder(Node* node, std::vector<int>& res) const;

        void destroy(Node* node);
};