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
        int value;
        int height;
        Node* left;
        Node* right;

        Node(int x) {
            value = x;
            height = 0;
            left = nullptr;
            right = nullptr;
        }
    };

    Node* root = nullptr;
    int tree_size = 0;
    int Height(Node* n);
    int HeightsDifference(Node* n);
    void changeHeight(Node* n);

    Node* rotateLeft(Node* n);
    Node* rotateRight(Node* n);
    Node* balance(Node* n);
    Node* insertValue(Node* n, int value, bool& inserted);
    Node* removeValue(Node* n, int value, bool& removed);
    Node* Min(Node* n);

    bool containsValue(Node* n, int value) const;
    void inorder(Node* n, std::vector<int>& res) const;
    void destructor(Node* n);
};
