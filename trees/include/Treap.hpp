#pragma "once"

#pragma once
#include <vector>
#include <cstddef>

class Treap
{
public:
    Treap();
    ~Treap();

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::vector<int> values() const;

    ~Treap();
};
private:
    struct Node
    {
        int key;
        int priority;
        Node *left;
        Node *right;
        Node(int k);
    };

    Node *root;
    std::size_t count;

    // Внутренние функции
    static Node *merge(Node *L, Node *R);
    static void split(Node *t, int key, Node *&L, Node *&R);
    void clear(Node *t);
    void inorder(Node *t, std::vector<int> &v) const;
};
