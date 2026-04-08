#pragma "once"

#include <cstddef>
#include <vector>

class Treap
{
private:
    struct Node
    {
        int key;
        int priority;
        Node* left;
        Node* right;

        Node(int value, int pr);
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    static Node* merge(Node* left, Node* right);
    static void split(Node* current, int value, Node*& left, Node*& right);
    static Node* insertNode(Node* current, Node* node);
    static Node* removeNode(Node* current, int value);
    static bool containsNode(Node* current, int value);
    static void inorder(Node* current, std::vector<int>& result);
    static void destroy(Node* current);
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();
};