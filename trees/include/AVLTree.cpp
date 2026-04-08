#include "AVLTree.hpp"
#include <algorithm>
#include <vector>

std::size_t AVLTree::size() const{
    return _size;
}

bool AVLTree::empty() const{
    return root == nullptr;
}

int AVLTree::getHeight(AVLTree::Node* n) const{
    if(n == nullptr) return -1;
    return n->height;
}

void AVLTree::updateHeight(AVLTree::Node* n){
    if(n){
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
    }
}

int AVLTree::getBalance(AVLTree::Node* n) const{
    if(!n) return 0;
    return getHeight(n->left) - getHeight(n->right);
}

AVLTree::Node* AVLTree::rotateLeft(AVLTree::Node* a){
    AVLTree::Node* b = a->right;
    a->right = b->left;
    b->left = a;
    updateHeight(a);
    updateHeight(b);
    return b;
}

AVLTree::Node* AVLTree::rotateRight(AVLTree::Node* a){
    AVLTree::Node* b = a->left;
    a->left = b->right;
    b->right = a;
    updateHeight(a);
    updateHeight(b);
    return b;
}

AVLTree::Node* AVLTree::bigRotateLeft(AVLTree::Node* a){
    a->right = rotateRight(a->right);
    return rotateLeft(a);
}

AVLTree::Node* AVLTree::bigRotateRight(AVLTree::Node* a){
    a->left = rotateLeft(a->left);
    return rotateRight(a);
}

bool AVLTree::contains(int value) const{
    return contains(root, value);
}

bool AVLTree::contains(AVLTree::Node* node, int value) const{
    if(node == nullptr) return false;
    if(value == node->value) return true;
    if(value < node->value) 
        return contains(node->left, value);
    else
        return contains(node->right, value);
}

bool AVLTree::insert(int value){
    if(contains(value)) return false;
    root = insert(root, value);
    _size++;
    return true;
}

AVLTree::Node* AVLTree::insert(AVLTree::Node* node, int value){
    if(node == nullptr){
        return new AVLTree::Node(value);
    }
    if(value < node->value){
        node->left = insert(node->left, value);
    }
    else if(value > node->value){
        node->right = insert(node->right, value);
    }
    else{
        return node;
    }

    updateHeight(node);

    int balance = getBalance(node);

    if(balance == -2){
        if(getBalance(node->right) <= 0){
            return rotateLeft(node);
        }
        else{
            return bigRotateLeft(node);
        }
    }
    if(balance == 2){
        if(getBalance(node->left) >= 0){
            return rotateRight(node);
        }
        else{
            return bigRotateRight(node);
        }
    }

    return node;
}

std::vector<int> AVLTree::values() const{
    std::vector<int> vec;
    inorderTraversal(root, vec);
    return vec;
}

void AVLTree::inorderTraversal(AVLTree::Node* node, std::vector<int>& result) const{
    if(node ==nullptr){
        return;
        
    }
    inorderTraversal(node->left, result);
    result.push_back(node->value);
    inorderTraversal(node->right, result);
}

void AVLTree::clear(AVLTree::Node* node){
    if(node == nullptr){
        return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
}

AVLTree::~AVLTree(){
    clear(root);
    root = nullptr;
    _size = 0;
}

AVLTree::Node* AVLTree::findMin(AVLTree::Node* node) const{
    if(node == nullptr){
        return nullptr;
    }
    
    if(node->left == nullptr){
        return node;
    }
    return findMin(node->left);
}

bool AVLTree::remove(int value){
    if(!contains(value)) return false;
    root = remove(root, value);
    _size--;
    return true;
}

AVLTree::Node* AVLTree::remove(AVLTree::Node* node, int value){
    if(node == nullptr){
        return nullptr;
    }

    if(value < node->value){
        node->left = remove(node->left, value);
    }    
    else if(value > node->value){
        node->right = remove(node->right, value);
    }
    else{
        if(node->left != nullptr && node->right != nullptr){
            AVLTree::Node* min_node = findMin(node->right);
            node->value = min_node->value;
            node->right = remove(node->right, min_node->value);
        }
        else if(node->left != nullptr){
            AVLTree::Node* child = node->left;
            delete node;
            return child;
        }
        else if(node->right !=nullptr){
            AVLTree::Node* child = node->right;
            delete node;
            return child;
        }
        else{
            delete node;
            return nullptr;
        }
    }

    updateHeight(node);

    int balance = getBalance(node);

    if(balance == -2){
        if(getBalance(node->right) <= 0){
            return rotateLeft(node);
        }
        else{
            return bigRotateLeft(node);
        }
    }
    if(balance == 2){
        if(getBalance(node->left) >= 0){
            return rotateRight(node);
        }
        else{
                return bigRotateRight(node);
        }
    }

    return node;
    
}