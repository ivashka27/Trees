#include "AVLTree.hpp"

#include <algorithm>

struct AVLTree::Node{
    explicit Node(int value) : value_(value), height_(0), left_(nullptr), right_(nullptr) {}

    int value_;
    int height_;
    Node* left_;
    Node* right_;
};

int AVLTree::get_height(const Node* node) {
    return node == nullptr ? -1 : node -> height_;
}

void AVLTree::update_height(Node* node) {
    node->height_ = std::max(get_height(node->left_), get_height(node->right_)) + 1;
}

int AVLTree::get_balance(Node* node) {
    return (node == nullptr) ? 0 : get_height(node->right_) - get_height(node->left_);
}

AVLTree::Node * AVLTree::rotate_right(Node* node) {
    Node * new_root = node->left_;
    Node * moved_subtree = new_root->right_;
    
    new_root->right_ = node;
    node->left_ = moved_subtree;
    
    update_height(node);
    update_height(new_root);
    
    return new_root;

}

AVLTree::Node * AVLTree::rotate_left(Node* node) {
    Node * new_root = node->right_;
    Node * moved_subtree = new_root->left_;
    
    new_root->left_ = node;
    node->right_ = moved_subtree;

    update_height(node);
    update_height(new_root);

    return new_root;
}

AVLTree::Node * AVLTree::rebalance(Node* node){
    int balance = get_balance(node);

    if (balance == -2){
        if(get_balance(node->left_) > 0) {node->left_ = rotate_left(node->left_);}
        return rotate_right(node);
    }
    else if (balance == 2){
        if(get_balance(node->right_) < 0) {node -> right_ = rotate_right(node->right_);}
        return rotate_left(node);
    }

    return node;
}

AVLTree::Node * AVLTree::insert_node(Node* node, const int value, bool & inserted) {
    if (node == nullptr){
        inserted = true;
        return new Node(value);
    }
    if (value < node->value_){
        node->left_ = insert_node(node->left_, value, inserted);
    }
    else if (value > node->value_){
        node->right_ = insert_node(node->right_, value, inserted);
    }
    else {
        return node;
    }

    update_height(node);
    return rebalance(node);
}

AVLTree::Node * AVLTree::get_max(Node* node){
    while(node->right_ != nullptr){
        node = node->right_;
    }
    return node;
}

// AVLTree::Node * AVLTree::get_min(Node * node){
//     if (node == nullptr) {return nullptr;}
//     if (node->left_ == nullptr) {return node;}
//     return get_max(node->left_);
// }


AVLTree::Node * AVLTree::remove_node(Node * node, const int value, bool & removed) {
    if (node == nullptr) {return nullptr;}
    else if (value < node->value_) {node->left_ = remove_node(node->left_, value, removed);}
    else if (value > node->value_) {node->right_ = remove_node(node->right_, value, removed);}
    else {
        removed = true;
        if (node->left_ == nullptr and node->right_ == nullptr){
            delete node;
            return nullptr;
        }
        if (node->left_ == nullptr){
            Node * right_child = node->right_;
            delete node;
            return right_child;
        }
        if (node->right_ == nullptr){
            Node * left_child = node->left_;
            delete node;
            return left_child;
        }
    
        Node * max_in_left = get_max(node->left_);
        node->value_ = max_in_left->value_;

        bool local_removed = false;
        node->left_ = remove_node(node->left_, max_in_left->value_, local_removed);
    }
    
    update_height(node);
    return rebalance(node);
}

bool AVLTree::contains_node(const Node* node, int value) {
    if (node == nullptr) {
        return false;
    }
    if(value < node->value_) {
        return contains_node(node->left_, value);
    }
    if (value > node->value_){
        return contains_node(node->right_, value);
    }

    return true;
}

void AVLTree::inorder(const Node* node, std::vector<int> & result){
    if (node == nullptr){
        return;
    }
    inorder(node->left_, result);
    result.push_back(node->value_);
    inorder(node->right_, result);
}

void AVLTree::clear_tree(Node* node){
    if (node == nullptr){
        return;
    }

    clear_tree(node->left_);
    clear_tree(node->right_);
    delete node;
}

bool AVLTree::contains(int value) const {
    return contains_node(root_, value);
}

bool AVLTree::insert(int value){
    bool inserted = false;
    root_ = insert_node(root_, value, inserted);

    if(inserted){
        ++size_;
    }

    return inserted;
}

bool AVLTree::remove(int value){
    bool removed = false;
    root_ = remove_node(root_, value, removed);

    if(removed){
        --size_;
    }

    return removed;
}

std::size_t AVLTree::size() const {
    return size_;
}

bool AVLTree::empty() const{
    return size_ == 0;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> result;
    result.reserve(size_);
    inorder(root_, result);
    return result;
}

AVLTree::~AVLTree() {
    clear_tree(root_);
}