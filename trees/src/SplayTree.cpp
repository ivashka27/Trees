#include "SplayTree.hpp"

SplayTree::rotateLeft(Node* x) const{
    if (x == nullptr || x->right == nullptr)
        return;
    Node* p = x->parent;
    Node* r = x->right;
    if (p != nullptr){
        if (p->left == x)
            p->left = r;
        else
            p->right = r;
    }else{
        root_ = r;
    }
    Node* tmp = r->left;
    r->left = x;
    x->right = tmp;
    x->parent = r;
    r->parent = p;
    if (tmp != nullptr)
        tmp->parent = x;
}

SplayTree::rotateRight(Node* x) const{
    if (x == nullptr || x->left == nullptr)
        return;
    Node* p = x->parent;
    Node* l = x->left;
    if (p != nullptr){
        if (p->right == x)
            p->right = l;
        else
            p->left = l;
    }else{
        root_ = l;
    }
    Node* tmp = l->right;
    l->right = x;
    x->left = tmp;
    x->parent = l;
    l->parent = p;
    if (tmp != nullptr)
        tmp->parent = x;
}

SplayTree::splay(Node* x) const{
    while (x->parent != nullptr){
        if (x == x->parent->left){
            if (x->parent->parent == nullptr){
                rotateRight(x->parent);
            }
            else if(x->parent == x->parent->parent->left){
                rotateRight(x->parent->parent);
                rotateRight(x->parent);
            }
            else{
                rotateRight(x->parent);
                rotateLeft(x->parent);
            }
        }
        else{
            if (x->parent->parent == nullptr){
                rotateLeft(x->parent);
            }
            else if (x->parent == x->parent->parent->right){
                rotateLeft(x->parent->parent);
                rotateLeft(x->parent);
            }
            else{
                rotateLeft(x->parent);
                rotateRight(x->parent);
            }
        }
    }
    root_ = x;
}

SplayTree::clear(Node* x){
    if (x != nullptr){
        clear(x->left);
        clear(x->right);
        delete x;
    }
}

SplayTree::~SplayTree(){
    clear(root_);
}

SplayTree::inorder(Node* node, std::vector<int>& out) const {
    if (node != nullptr){
        inorder(node->left, out);
        out.push_back(node->value);
        inorder(node->right, out);
    }
}

SplayTree::size() const{
    return size_;
}

SplayTree::empty() const{
    return size_ == 0;
}

SplayTree::values() const{
    std::vector<int> out;
    inorder(root_, out);
    return out;
}

SplayTree::findNode(int value) const{
    if (root_ == nullptr)
        return nullptr;
    Node* current = root_;
    while (current != nullptr){
        if (current->value == value)
            return current;
        else if (current->value < value)
            current = current->right;
        else
            current = current->left;
    }
    return nullptr;
}
SplayTree::findLast(int value) const{
    Node* current = root_;
    Node* last = nullptr;
    while (current != nullptr){
        last = current;
        if (current->value == value) return current;
        current = (value > current->value) ? current->right : current->left;
    }
    return last;
}

SplayTree::contains(int value) const{
    Node* found = findNode(value);
    if (found != nullptr){
        splay(found);
        return true;
    }
    Node* last = findLast(value);
    if (last != nullptr){
        splay(last);
        return false;
    }
    return false;
}