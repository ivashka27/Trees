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
        struct node;

        node* root = nullptr;
        std::size_t tree_size = 0;

        static int getHeight(node* n);
        static void newHeight(node* n);
        static int balanceFactor(node* n);
        static node* rotate_left(node* n);
        static node* rotate_right(node* n);
        static node* balance(node* n);

        node* insertNode(node* n, int key);
        node* removeNode(node* n, int key);

        bool containsNode(const node* n, int value) const;
        void collectValues(const node* n, std::vector<int>& out) const;

        static void destroy(node* n);

        AVLTree(const AVLTree&) = delete;
        AVLTree& operator=(const AVLTree&) = delete;
};
