#include "SplayTree.hpp"

void SplayTree::rotateLeft(Node* x) const{
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

void SplayTree::rotateRight(Node* x) const{
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

void SplayTree::splay(Node* x) const{
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

void SplayTree::clear(Node* x){
    if (x != nullptr){
        clear(x->left);
        clear(x->right);
        delete x;
    }
}

SplayTree::~SplayTree(){
    clear(root_);
}

void SplayTree::inorder(Node* node, std::vector<int>& out) const {
    if (node != nullptr){
        inorder(node->left, out);
        out.push_back(node->value);
        inorder(node->right, out);
    }
}

std::size_t SplayTree::size() const{
    return size_;
}

bool SplayTree::empty() const{
    return size_ == 0;
}

std::vector<int> SplayTree::values() const{
    std::vector<int> out;
    inorder(root_, out);
    return out;
}

SplayTree::Node* SplayTree::findNode(int value) const{
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
SplayTree::Node* SplayTree::findLast(int value) const{
    Node* current = root_;
    Node* last = nullptr;
    while (current != nullptr){
        last = current;
        if (current->value == value) return current;
        current = (value > current->value) ? current->right : current->left;
    }
    return last;
}

SplayTree::Node* SplayTree::subtreeMax(Node* node) const{
    if (node == nullptr)
        return nullptr;
    Node* current = node;
    while (current->right != nullptr)
        current = current->right;
    return current;
}

bool SplayTree::contains(int value) const{
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

/*
func insert(x : Node, z : Node):            // x — корень поддерева, z — вставляемый элемент
   while x != null
     if z.key > x.key
        if x.right != null
           x = x.right
        else
           z.parent = x
           x.right = z
           break
     else if z.key < x.key
        if x.left != null
           x = x.left
        else
           z.parent = x
           x.left = z
           break
*/
bool SplayTree::insert(int value){
    if (root_ == nullptr){
        root_ = new Node{nullptr, nullptr, nullptr, value};
        size_ = 1;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;
    while (current != nullptr){
        parent = current;
        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else {
            // Значение уже есть: поднимем найденный узел наверх.
            splay(current);
            return false;
        }
    }

    Node* z = new Node{nullptr, nullptr, parent, value};
    if (value < parent->value)
        parent->left = z;
    else
        parent->right = z;
    splay(z);
    ++size_;
    return true;
}

bool SplayTree::remove(int value){
    if (root_ == nullptr)
        return false;
    Node* found = findNode(value);
    if (found == nullptr){
        // Аналогично `contains`: поднимем "последний посещённый" узел.
        Node* last = findLast(value);
        if (last != nullptr)
            splay(last);
        return false;
    }
    // Поднимаем удаляемый узел в корень.
    splay(found);

    Node* left = root_->left;
    Node* right = root_->right;
    if (left != nullptr)
        left->parent = nullptr;
    if (right != nullptr)
        right->parent = nullptr;

    delete root_;
    root_ = nullptr;
    --size_;

    if (left == nullptr){
        root_ = right;
        return true;
    }

    // Максимум в левом поддереве станет новым корнем.
    Node* m = subtreeMax(left);
    splay(m); // теперь `root_ == m`

    root_->right = right;
    if (right != nullptr)
        right->parent = root_;
    return true;
}