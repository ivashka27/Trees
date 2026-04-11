#include "SplayTree.hpp"





std::size_t SplayTree::size() const {
    return size_;
}

bool SplayTree::empty() const {
    return size_ == 0;
}



SplayTree::Node* SplayTree::findNode(int value) const {
    Node* current = root_;

    while (current != nullptr) {
        if (current->value == value) {
            return current;
        }
        if (current->value > value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return nullptr;
}


bool SplayTree::contains(int value) const {
    if (findNode(value) == nullptr){
        return false;
    } 
    return true;
    
}



void SplayTree::inorderTraversal(Node* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left, result);
    result.push_back(node->value);
    inorderTraversal(node->right, result);
}



std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    result.reserve(size_);
    inorderTraversal(root_, result);
    return result;
}



void SplayTree::deleteSubtree(Node* node) {
    if (node == nullptr) {
        return;
    }

    deleteSubtree(node->left);
    deleteSubtree(node->right);
    delete node;
}



SplayTree::~SplayTree() {
    deleteSubtree(root_);
}



void SplayTree::rotateLeft(Node* x) {
    Node* y = x->right;
    if (y == nullptr) {
        return;
    }

    x->right = y->left;
    if (y->left != nullptr) {
        y->left->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root_ = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
}




void SplayTree::rotateRight(Node* x) {
    Node* y = x->left;
    if (y == nullptr) {
        return;
    }

    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x;
    }

    y->parent = x->parent;

    if (x->parent == nullptr) {
        root_ = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }

    y->right = x;
    x->parent = y;
}



void SplayTree::splay(Node* x) {
    if (x == nullptr) {
        return;
    }

    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent;

        if (g == nullptr) {
            if (x == p->left) {
                rotateRight(p);
            } else {
                rotateLeft(p);
            }
        } else if (x == p->left && p == g->left) {
            rotateRight(g);
            rotateRight(p);
        } else if (x == p->right && p == g->right) {
            rotateLeft(g);
            rotateLeft(p);
        } else if (x == p->right && p == g->left) {
            rotateLeft(p);
            rotateRight(g);
        } else {
            rotateRight(p);
            rotateLeft(g);
        }
    }
}



SplayTree::Node* SplayTree::subtreeMin(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->left != nullptr) {
        node = node->left;
    }

    return node;
}

SplayTree::Node* SplayTree::subtreeMax(Node* node) const {
    if (node == nullptr) {
        return nullptr;
    }

    while (node->right != nullptr) {
        node = node->right;
    }

    return node;
}




bool SplayTree::insert(int value) {
    if (root_ == nullptr) {
        root_ = new Node(value);
        size_ = 1;
        return true;
    }

    Node* current = root_;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;

        if (value == current->value) {
            splay(current);
            return false;
        }

        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    Node* newNode = new Node(value);
    newNode->parent = parent;

    if (value < parent->value) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    splay(newNode);
    ++size_;
    return true;
}



bool SplayTree::remove(int value) {
    Node* nodeToRemove = findNode(value);
    if (nodeToRemove == nullptr) {
        return false;
    }

    splay(nodeToRemove);

    Node* leftSubtree = root_->left;
    Node* rightSubtree = root_->right;

    if (leftSubtree != nullptr) {
        leftSubtree->parent = nullptr;
    }
    if (rightSubtree != nullptr) {
        rightSubtree->parent = nullptr;
    }

    delete root_;
    root_ = nullptr;
    --size_;

    if (leftSubtree == nullptr) {
        root_ = rightSubtree;
        return true;
    }

    root_ = leftSubtree;

    Node* maxLeft = subtreeMax(root_);
    splay(maxLeft);

    root_->right = rightSubtree;
    if (rightSubtree != nullptr) {
        rightSubtree->parent = root_;
    }

    return true;
}