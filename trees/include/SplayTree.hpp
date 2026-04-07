#pragma "once"

#include <vector>

class SplayTree
{
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
    
    
    void rotate_right(Node* x); // for splay operations:
    void rotate_left(Node* x);  // zig, zig-zig, zig-zag
    void clear(Node* node); 
    void splay(Node* x);

    Node* find_max(Node* node); // for merge operation

    // for contains 
    Node* find(int value);                        

    // for insert and remove
    Node* merge(Node* left_tree, Node* right_tree); 

    // for values
    void get_values(Node* node, std::vector<int>& result) const; 

public:
    bool contains(int value) const;
    bool insert(int value); 
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();
};
