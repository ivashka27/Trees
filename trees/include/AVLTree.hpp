#pragma once
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
struct Node { 
	int key; 
	Node* right;
	Node* left;
	int height;
	Node(int value);
};
Node* root=nullptr;
std::size_t tree_size = 0;
int get_height(Node* node) const;
int update_node_height(Node*node) const;
int bf(Node* node) const;
Node* rightRotate(Node* node);
Node* leftRotate(Node* node);
Node* doBalance(Node* node);
Node* find_min(Node* node) const;
Node* balance_insert(Node* node, int value);
Node* removeNode(Node* node, int value);
void in_order_values(Node* node, std::vector<int>& values) const;
void destroy(Node* node);
};

