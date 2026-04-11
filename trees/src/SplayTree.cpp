#include "SplayTree.hpp"

SplayTree::~SplayTree() {
    destroyTree(root);
}

void SplayTree::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

std::size_t SplayTree::size() const {
    return node_count;
}

bool SplayTree::empty() const {
    return node_count == 0;
}

void SplayTree::inOrderTraversal(Node* node, std::vector<int>& result) const {
    if (node != nullptr) {
        inOrderTraversal(node->left, result);
        result.push_back(node->value);
        inOrderTraversal(node->right, result);
    }
}

std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    result.reserve(node_count);
    inOrderTraversal(root, result);
    return result;
}

void SplayTree::leftRotate(Node* x) const {
    Node* y = x->right;
    x->right = y->left;
    
    if (y->left != nullptr) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;
}

void SplayTree::rightRotate(Node* x) const {
    Node* y = x->left;
    x->left = y->right;
    
    if (y->right != nullptr) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;
    x->parent = y;
}

void SplayTree::splay(Node* x) const {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
        if (x->parent->parent == nullptr) {
            if (x == x->parent->left) {
                rightRotate(x->parent);
            } else {
                leftRotate(x->parent);
            }
        } else if (x == x->parent->left && x->parent == x->parent->parent->left) {
            rightRotate(x->parent->parent);
            rightRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->right) {
            leftRotate(x->parent->parent);
            leftRotate(x->parent);
        } else if (x == x->parent->right && x->parent == x->parent->parent->left) {
            leftRotate(x->parent);
            rightRotate(x->parent);
        } else {
            rightRotate(x->parent);
            leftRotate(x->parent);
        }
    }
    root = x;
}

bool SplayTree::contains(int value) const {
    if (root == nullptr) return false;

    Node* current = root;
    Node* lastAccessed = nullptr;

    while (current != nullptr) {
        lastAccessed = current;
        if (value == current->value) {
            splay(current);
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    splay(lastAccessed); 
    return false;
}

bool SplayTree::insert(int value) {
    if (root == nullptr) {
        root = new Node(value);
        node_count++;
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;

    while (current != nullptr) {
        parent = current;
        if (value == current->value) {
            splay(current);
            return false;
        } else if (value < current->value) {
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
    node_count++;
    return true;
}

bool SplayTree::remove(int value) {
    if (!contains(value)) {
        return false; 
    }

    Node* target = root;

    if (root->left == nullptr) {
        root = root->right;
        if (root != nullptr) {
            root->parent = nullptr;
        }
    } else {
        Node* rightSubtree = root->right;
        
        root = root->left;
        root->parent = nullptr;

        Node* maxLeft = root;
        while (maxLeft->right != nullptr) {
            maxLeft = maxLeft->right;
        }

        splay(maxLeft);

        root->right = rightSubtree;
        if (rightSubtree != nullptr) {
            rightSubtree->parent = root;
        }
    }

    delete target; 
    node_count--;
    return true;
}