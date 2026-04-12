#include "AVLTree.hpp"
#include <algorithm>

int AVLTree::Height(Node* n) {
    if (n == nullptr) return -1;
    else {return n->height;}
}

void AVLTree::changeHeight(Node* n) {
    int left_height = Height(n->left);
    int right_height = Height(n->right);
    if (left_height > right_height) {n->height = left_height + 1;}
    else {n->height = right_height + 1;}
}

int AVLTree::HeightsDifference(Node* n) {
    return Height(n->left) - Height(n->right);
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    changeHeight(y);
    changeHeight(x);

    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    changeHeight(x);
    changeHeight(y);

    return y;
}

AVLTree::Node* AVLTree::balance(Node* n) {
    changeHeight(n);

    int hd = HeightsDifference(n);

    if (hd > 1) {
        if (HeightsDifference(n->left) < 0) {
            n->left = rotateLeft(n->left);
	}
	return rotateRight(n);
        
    }

    if (hd < -1) {
        if (HeightsDifference(n->right) > 0) {
            n->right = rotateRight(n->right);
	}
        return rotateLeft(n);
    }

    return n;
}

AVLTree::Node* AVLTree::insertValue(Node* n, int value, bool& inserted) {
    if (n == nullptr) {
        inserted = true;
        return new Node(value);
    }

    if (value == n->value) {
        inserted = false;
        return n;
    }

    if (value < n->value)
        n->left = insertValue(n->left, value, inserted);
    else
        n->right = insertValue(n->right, value, inserted);

    return balance(n);
}

bool AVLTree::insert(int value) {
    bool inserted = false;
    root = insertValue(root, value, inserted);
    if (inserted) {tree_size++;}
    return inserted;
}

bool AVLTree::containsValue(Node* n, int value) const {
    if (n == nullptr) return false;

    if (value < n->value)
        return containsValue(n->left, value);
    if (value > n->value)
        return containsValue(n->right, value);

    return true;
}

bool AVLTree::contains(int value) const {
    return containsValue(root, value);
}

AVLTree::Node* AVLTree::Min(Node* n) {
    while (n->left != nullptr)
        n = n->left;
    return n;
}

AVLTree::Node* AVLTree::removeValue(Node* n, int value, bool& removed) {
    if (n == nullptr) {
        removed = false;
        return nullptr;
    }

    if (value < n->value) {
        n->left = removeValue(n->left, value, removed);

}
    else if (value > n->value) {
        n->right = removeValue(n->right, value, removed);
    }
    else {
        removed = true;

        if (n->left == nullptr || n->right == nullptr) {
            Node* temp;
            if (n->left != nullptr)
                temp = n->left;
            else
                temp = n->right;

            delete n;
            return temp;
        }

        Node* min = Min(n->right);
        n->value = min->value;
        n->right = removeValue(n->right, min->value, removed);
    }

    return balance(n);
}

bool AVLTree::remove(int value) {
    bool removed = false;
    root = removeValue(root, value, removed);
    if (removed) tree_size--;
    return removed;
}

void AVLTree::inorder(Node* n, std::vector<int>& res) const {
    if (n == nullptr) return;

    inorder(n->left, res);
    res.push_back(n->value);
    inorder(n->right, res);
}

std::vector<int> AVLTree::values() const {
    std::vector<int> res;
    inorder(root, res);
    return res;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::empty() const {
    return tree_size == 0;
}

void AVLTree::destructor(Node* n) {
    if (n == nullptr) return;

    destructor(n->left);
    destructor(n->right);
    delete n;
}

AVLTree::~AVLTree() {
    destructor(root);
}
