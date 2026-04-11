#pragma "once"

#include <vector>

class Treap
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();


private:
    struct Node 
    {
        int value;
        int priority;
        Node* left;
        Node* right;

        Node(int val);

    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;

    static void split(Node* t, int key, Node*& left, Node*& right);
    static Node* merge(Node* left, Node* right);

    bool contains(Node* node, int value) const;
    void collect(Node* node, std::vector<int>& result) const;
    void clear(Node* node);
};