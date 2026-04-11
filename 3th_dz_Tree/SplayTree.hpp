#pragma once

#include <vector>






class SplayTree
{
public:


    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();




    private:
        struct Node {
            int value;
            Node* left;
            Node* right;
            Node* parent;

            explicit Node(int v)
                : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
        };

        Node* root_ = nullptr;
        std::size_t size_ = 0;




    private:
        void rotateLeft(Node* x);
        void rotateRight(Node* x);
        void splay(Node* x);

        Node* findNode(int value) const;
        Node* subtreeMin(Node* node) const;
        Node* subtreeMax(Node* node) const;

        void inorderTraversal(Node* node, std::vector<int>& result) const;
        void deleteSubtree(Node* node);
};