#include "../include/SplayTree.hpp"
#include <vector>
#include <algorithm>
#include <utility>

void SplayTree::clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::rotate_right(Node* x) {
    Node* p = x->parent;
    if (!p) return;
    
    Node* g = p->parent;
    p->left = x->right;

    if (x->right) x->right->parent = p;
    x->right = p;
    p->parent = x;
    
    x->parent = g;
    if (g) {
        if (g->left == p) g->left = x;
        else g->right = x;
    } else {
        root = x;
    }
}

void SplayTree::rotate_left(Node* x) {
    Node* p = x->parent;
    if (!p) return;
    
    Node* g = p->parent;
    p->right = x->left;

    if (x->left) x->left->parent = p;
    x->left = p;
    p->parent = x;
    
    x->parent = g;
    if (g) {
        if (g->left == p) g->left = x;
        else g->right = x;
    } else {
        root = x;
    }
}

void SplayTree::splay(Node* x) {
    if (!x) return;
    
    while (x->parent) {
        Node* p = x->parent;
        Node* g = p->parent;
        
        if (!g) {
            // zig
            if (x == p->left) {
                rotate_right(x);
            } else {
                rotate_left(x);
            }
        } else if (x == p->left && p == g->left) {
            // zig-zig 
            rotate_right(p);
            rotate_right(x);
        } else if (x == p->right && p == g->right) {
            // zig-zig 
            rotate_left(p);
            rotate_left(x);
        } else if (x == p->left && p == g->right) {
            // zig-zag
            rotate_right(x);
            rotate_left(x);
        } else {
            // zig-zag 
            rotate_left(x);
            rotate_right(x);
        }
    }
    root = x;
}

SplayTree::Node* SplayTree::find(int value) {
    Node* current = root;
    Node* last = nullptr;
    
    while (current) {
        last = current;
        
        if (value == current->value) {
            splay(current);
            return current;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    if (last) splay(last);
    
    return nullptr;
}

SplayTree::Node* SplayTree::find_max(Node* node) {
    if (!node) return nullptr;
    while (node->right) node = node->right;
    splay(node);
    return node;
}

SplayTree::Node* SplayTree::merge(Node* left_tree, Node* right_tree) {
    if (!left_tree) return right_tree;
    if (!right_tree) return left_tree;
    
    Node* maxLeft = find_max(left_tree);
    splay(maxLeft);
    maxLeft->right = right_tree;
    right_tree->parent = maxLeft;
    
    return maxLeft;
}

void SplayTree::get_values(Node* node, std::vector<int>& result) const {
    if (!node) return;
    get_values(node->left, result);
    result.push_back(node->value);
    get_values(node->right, result);
}

bool SplayTree::contains(int value) const {
    Node* node = const_cast<SplayTree*>(this)->find(value);
    return node && node->value == value;
}

bool SplayTree::insert(int value) {
    if (contains(value)) return false;
    
    Node* new_node = new Node(value);
    
    if (!root) root = new_node;
    else {
        Node* current = root;
        while (true) {
            if (value < current->value) {
                if (!current->left) {
                    current->left = new_node;
                    new_node->parent = current;
                    break;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new_node;
                    new_node->parent = current;
                    break;
                }
                current = current->right;
            }
        }
        splay(new_node);
    }
    
    tree_size++;
    return true;
}

bool SplayTree::remove(int value) {
    Node* node = find(value);
    if (!node || node->value != value) return false;
    
    splay(node);
    
    Node* left_tree = root->left;
    Node* right_tree = root->right;
    
    if (left_tree) left_tree->parent = nullptr;
    if (right_tree) right_tree->parent = nullptr;
    
    delete root;
    root = merge(left_tree, right_tree);
    tree_size--;
    return true;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    get_values(root, result);
    return result;
}