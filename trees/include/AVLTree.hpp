#pragma "once"

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
    std::size_t tree_size = 0;
    
    struct node
    {
        int key;
        unsigned int height;
        node* left;
        node* right;
        node(int k) {key = k; left=right=0; height = 1;}
    };
    node* root = nullptr;

    unsigned int get_h(node* node) const;
    int bfactor(node* node) const;
    void update_h(node* node);

    node* rotate_r(node* node);
    node* rotate_l(node* node);

    node* balance(node* node);
    node* insert(node* node, int k);

    node* findmin(node* node);
    node* removemin(node* node);

    node* remove(node* node, int k);
    void clear(node* node);
    
    void in_order(node* node, std::vector<int>& values) const;
};
