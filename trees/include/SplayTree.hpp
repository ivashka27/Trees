#ifndef SPLAYTREE_HPP
#define SPLAYTREE_HPP

#include <cstddef>
#include <vector>

class SplayTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val);
    };

    Node* root;
    std::size_t tree_size;

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void splay(Node* x);
    Node* findNode(int value);
    Node* findMax(Node* node);
    void inorder(Node* node, std::vector<int>& vec) const;
    void clear(Node* node);

public:
    SplayTree();
    ~SplayTree();

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    bool contains(int value);
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;
};

#endif
