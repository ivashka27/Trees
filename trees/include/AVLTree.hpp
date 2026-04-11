#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include <vector>

class AVLTree
{
private:
    struct Node
    {
        int value;
        Node* left;
        Node* right;
        int height;

        Node(int val) : value(val), left(nullptr), right(nullptr), height(0) {}
    };

    Node* root_;
    std::size_t size_;

    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    void updateHeight(Node* node);

    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);

    
    Node* insert(Node* node, int value, bool& inserted);
    Node* remove(Node* node, int value, bool& removed);
    Node* balance(Node* node);

    Node* findMin(Node* node) const;
    Node* removeMin(Node* node);

    void inorder(Node* node, std::vector<int>& result) const;

    void destroy(Node* node);

    bool contains(Node* node, int value) const;
public:
    AVLTree() : root_(nullptr), size_(0) {}
    
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();
};

#endif // AVL_TREE_HPP
