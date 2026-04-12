#include "SplayTree.hpp"

void SplayTree::clear(Node* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

SplayTree::~SplayTree() {
    clear(root);
}

void SplayTree::rotate_right(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void SplayTree::rotate_left(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void SplayTree::splay(Node* x) const {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent;

        if (g == nullptr) {
            if (x == p->left) {
                rotate_right(p);
            }
            else {
                rotate_left(p);
            }
        }
        else {
            if (x == p->left && p == g->left) {
                rotate_right(g);
                rotate_right(p);
            }
            else if (x == p->right && p == g->right) {
                rotate_left(g);
                rotate_left(p);
            }
            else if (x == p->right && p == g->left) {
                rotate_left(p);
                rotate_right(g);
            }
            else {
                rotate_right(p);
                rotate_left(g);
            }
        }
    }
}

bool SplayTree::contains(int value) const {
    Node* curr = root;
    Node* last = nullptr;

    while (curr != nullptr) {
        last = curr;
        if (curr->value == value) {
            splay(curr);
            return true;
        }
        else if (value < curr->value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    if (last != nullptr) {
        splay(last);
    }
    return false;
}

bool SplayTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        tree_size++;
        return true;
    }

    Node* curr = root;
    Node* p = nullptr;

    while (curr != nullptr) {
        p = curr;
        if (value == curr->value) {
            splay(curr);
            return false;
        }
        if (value < curr->value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }

    Node* newNode = new Node(value);
    newNode->parent = p;
    if (value < p->value) {
        p->left = newNode;
    }
    else {
        p->right = newNode;
    }

    splay(newNode);
    tree_size++;
    return true;
}

bool SplayTree::remove(int value) {
    if (!contains(value)) return false;

    Node* oldRoot = root;

    if (root->left == nullptr) {
        root = root->right;
        if (root != nullptr) {
            root->parent = nullptr;
        }
    }
    else {
        Node* L = root->left;
        Node* R = root->right;
        L->parent = nullptr;

        Node* maxL = L;
        while (maxL->right != nullptr) {
            maxL = maxL->right;
        }

        this->root = L;
        splay(maxL);

        this->root->right = R;
        if (R != nullptr) {
            R->parent = this->root;
        }
    }

    delete oldRoot;
    tree_size--;
    return true;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

void SplayTree::collect_values(Node* node, std::vector<int>& v) const {
    if (node == nullptr) return;
    collect_values(node->left, v);
    v.push_back(node->value);
    collect_values(node->right, v);
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    collect_values(root, result);
    return result;
}