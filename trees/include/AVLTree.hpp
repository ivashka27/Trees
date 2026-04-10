#pragma "once"

#include <vector>
#include <cstddef>

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
        Node *left = nullptr, *right = nullptr;
        int height = 1;
        Node(int val) : value(val) {}
    };

    Node* root = nullptr;
    std::size_t tree_size = 0;

    int height(Node* n) const;
    int get_balance(Node* n) const;
    void update_height(Node* n);
    Node* rotate_right(Node* y);
    Node* rotate_left(Node* x);
    Node* balance(Node* n);
    
    Node* insert_recursive(Node* n, int val, bool& success);
    Node* remove_recursive(Node* n, int val, bool& success);
    Node* find_min(Node* n) const;
    Node* remove_min(Node* n);
    
    void clear(Node* n);
    void traverse(Node* n, std::vector<int>& res) const;
};