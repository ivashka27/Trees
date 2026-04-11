#include "AVLTree.hpp"

int AVLTree::height(Node* p) const {
    return p ? p->height : 0;
}

int AVLTree::balance_factor(Node* p) const {
    return height(p->right) - height(p->left);
}

void AVLTree::fix_height(Node* p) {
    int hl = height(p->left);
    int hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

AVLTree::Node* AVLTree::rotate_right(Node* p) {
    Node* q = p->left;
    p->left = q->right;
    q->right = p;
    fix_height(p);
    fix_height(q);
    return q;
}

AVLTree::Node* AVLTree::rotate_left(Node* q) {
    Node* p = q->right;
    q->right = p->left;
    p->left = q;
    fix_height(q);
    fix_height(p);
    return p;
}

AVLTree::Node* AVLTree::balance(Node* p) {
    fix_height(p);
    
    if (balance_factor(p) == 2) {
        if (balance_factor(p->right) < 0) {
            p->right = rotate_right(p->right);
        }
        return rotate_left(p);
    }
    
    if (balance_factor(p) == -2) {
        if (balance_factor(p->left) > 0) {
            p->left = rotate_left(p->left);
        }
        return rotate_right(p);
    }
    
    return p;
}



bool AVLTree::empty() const {
    return root == nullptr;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::contains(int value) const {
    Node* curr = root; 
    while (curr) {
        if (value == curr->key) return true;
        curr = (value < curr->key) ? curr->left : curr->right;
    }
    return false;
}

bool AVLTree::insert(int value) {
    bool inserted = false; 
    root = insert(root, value, inserted); 
    if (inserted) tree_size++; 
    return inserted; 
}


AVLTree::Node* AVLTree::insert(Node* p, int k, bool& inserted) {
    if (!p) { 
        inserted = true;
        return new Node(k);
    }
    if (k < p->key) {
        p->left = insert(p->left, k, inserted); 
    } else if (k > p->key) { 
        p->right = insert(p->right, k, inserted); 
    } else {
        inserted = false;
        return p;
    }
    return balance(p); 
}

bool AVLTree::remove(int value) {
    bool removed = false; 
    root = remove(root, value, removed); 
    if (removed) tree_size--; 
    return removed; 
}


AVLTree::Node* AVLTree::find_min(Node* p) const {
    return p->left ? find_min(p->left) : p; 
}

AVLTree::Node* AVLTree::remove_min(Node* p) {
    if (p->left == nullptr) {
        return p->right;
    }
    p->left = remove_min(p->left); 
    return balance(p);
}

AVLTree::Node* AVLTree::remove(Node* p, int k, bool& removed) {
    if (!p) { 
        removed = false;
        return nullptr; 
    }
    if (k < p->key) { 
        p->left = remove(p->left, k, removed);
    } else if (k > p->key) { 
        p->right = remove(p->right, k, removed);
    } else {
        removed = true; 
        Node* l = p->left; 
        Node* r = p->right; 
        delete p;
        
        if (!r) return l;
        
        Node* min = find_min(r); 
        min->right = remove_min(r);
        min->left = l;
        return balance(min); 
    }
    return balance(p);
}


std::vector<int> AVLTree::values() const {
    std::vector<int> result; 
    result.reserve(tree_size); 
    collect_values(root, result);
    return result;
}


void AVLTree::collect_values(Node* p, std::vector<int>& res) const {
    if (!p) return; 
    collect_values(p->left, res); 
    res.push_back(p->key); 
    collect_values(p->right, res);
}

AVLTree::~AVLTree() {
    clear(root);
}


void AVLTree::clear(Node* p) {
    if (!p) return; 
    clear(p->left); 
    clear(p->right); 
    delete p; 
}