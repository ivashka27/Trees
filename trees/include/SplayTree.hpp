#pragma "once"

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

        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    void rotate_right(Node* x);
    void rotate_left(Node* x);
    void splay(Node* x); 
    void clear(Node* node);

    void collect_values(Node* node, std::vector<int>& v) const;
};