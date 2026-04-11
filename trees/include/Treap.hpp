#pragma once

#include <vector>
#include <cstddef>
#include <utility>

class Treap {
public:

    Treap();


    ~Treap();


    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;


    bool contains(int value) const;


    bool insert(int value);


    bool remove(int value);


    std::size_t size() const;


    bool empty() const;

    std::vector<int> values() const;

private:


    struct Node {
        int value;        
        int priority;     
        Node* left;       
        Node* right;      

     
        Node(int val);
    };

    Node* root;           
    std::size_t tree_size; 


    Node* merge(Node* left, Node* right);


    std::pair<Node*, Node*> split(Node* node, int key);


    Node* find(Node* node, int value) const;

    void collect_values(Node* node, std::vector<int>& result) const;


    void delete_subtree(Node* node);
};