#include "AVLTree.hpp"

#include <algorithm>

struct AVLTree::node{
    int key;
    int height;
    node* left;
    node* right;

    node(int k) : key(k), height(0), left(nullptr), right(nullptr) {}
};

int AVLTree::getHeight(node* n){
    return n ? n->height : -1;
}

void AVLTree::newHeight(node* n){
    n -> height = std::max(getHeight(n->left), getHeight(n -> right)) + 1;
}

int AVLTree::balanceFactor(node* n){
    return getHeight(n->right) - getHeight(n->left);
}

AVLTree::node* AVLTree::rotate_left(node* n){
    node* n2 = n->right;
    n->right = n2->left;
    n2->left = n;
    newHeight(n);
    newHeight(n2);

    return n2;
}

AVLTree::node* AVLTree::rotate_right(node* n){
    node* n2 = n->left;
    n->left = n2->right;
    n2->right = n;
    newHeight(n);
    newHeight(n2);

    return n2;
}

AVLTree::node* AVLTree::balance(node* n){
    newHeight(n);
    int balance_factor = balanceFactor(n);

    if (balance_factor == 2){
        if (balanceFactor(n->right) < 0){
            n->right = rotate_right(n->right);
        }
        return rotate_left(n);
    }
    if (balance_factor == -2){
        if (balanceFactor(n->left) > 0){
            n->left = rotate_left(n->left);
        }
        return rotate_right(n);
    }
    return n;
}

AVLTree::node* AVLTree::insertNode(node* n, int key){
    if (!n){
        return new node(key);
    }

    if (key < n->key){
        n->left = insertNode(n->left, key);
    }
    else if (key > n->key){
        n->right = insertNode(n->right, key);
    }

    return balance(n);
}

AVLTree::node* AVLTree::removeNode(node* n, int key){
    if (!n){
        return nullptr;
    }

    if (key < n->key){
        n->left = removeNode(n->left, key);
    }
    else if (key > n->key){
        n->right = removeNode(n->right, key);
    }
    else{
        if (!n->left && !n->right){
            delete n;
            return nullptr;
        }
        if (!n->left){
            node* t = n->right;
            delete n;
            return t;
        }
        if (!n->right){
            node* t = n->left;
            delete n;
            return t;
        }
        node* succ = n->right;
        while (succ->left){
            succ = succ->left;
        }
        n->key = succ->key;
        n->right = removeNode(n->right, succ->key);
    }

    return balance(n);
}

bool AVLTree::containsNode(const node* n, int value) const{
    if (!n){
        return false;
    }
    if (value < n->key){
        return containsNode(n->left, value);
    }
    if (value > n->key){
        return containsNode(n->right, value);
    }
    return true;
}

bool AVLTree::contains(int value) const{
    return containsNode(root, value);
}

bool AVLTree::insert(int value){
    if (contains(value)){
        return false;
    }
    root = insertNode(root, value);
    ++tree_size;
    return true;
}

bool AVLTree::remove(int value){
    if (!contains(value)){
        return false;
    }
    root = removeNode(root, value);
    --tree_size;
    return true;
}

std::size_t AVLTree::size() const{
    return tree_size;
}

bool AVLTree::empty() const{
    return tree_size == 0;
}

void AVLTree::collectValues(const node* n, std::vector<int>& out) const{
    if (!n){
        return;
    }
    collectValues(n->left, out);
    out.push_back(n->key);
    collectValues(n->right, out);
}

std::vector<int> AVLTree::values() const{
    std::vector<int> out;
    collectValues(root, out);
    return out;
}

void AVLTree::destroy(node* n){
    if (!n){
        return;
    }
    destroy(n->left);
    destroy(n->right);
    delete n;
}

AVLTree::~AVLTree(){
    destroy(root);
    root = nullptr;
    tree_size = 0;
}

