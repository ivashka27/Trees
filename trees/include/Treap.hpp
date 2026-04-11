#pragma "once"

#include <vector>

class Treap {
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();

private:
    struct Node;
    Node* root = nullptr;
    std::size_t sz = 0;

    void split(Node*, int, Node*&, Node*&);
    Node* merge(Node*, Node*);
    bool contains(Node*, int) const;
    Node* remove(Node*, int, bool&);
    void inorder(Node*, std::vector<int>&) const;
    void clear(Node*);
};