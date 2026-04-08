#include "AVLTree.hpp"

bool AVLTree::contains (int value) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->key == value) {
            return true;
        }
        else if (curr->key > value) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    return false;
}

bool AVLTree::insert(int value) {
    if (this->contains(value)) {
        return false;
    }
    root = insert_node(root, value);
    tree_size += 1;
    return true;
}

bool AVLTree::remove(int value) {
    if (!(this->contains(value))) {
        return false;
    }
    root = remove_node(root, value);
    tree_size -= 1;
    return true;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::empty() const {
    return root == nullptr;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> val;
    in_order(root, val);
    return val;
}

AVLTree::~AVLTree() {
    destroy(root);
    root = nullptr;
};

AVLTree::Node::Node (int value) {
    key = value;
    left = nullptr;
    right = nullptr;
    height = 0;
}

int AVLTree::get_height(Node* node) const {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}

int AVLTree::update_height(Node* node) {
    return std::max(get_height(node->left), get_height(node->right)) + 1;
}

int AVLTree::get_balance(Node* node) const {
    return (get_height(node->left) - get_height(node->right));
}

AVLTree::Node* AVLTree::right_rotate(Node* node) {
    Node* new_node = node->left;
    node->left = new_node->right;
    new_node->right = node;
    node->height = update_height(node);
    new_node->height = update_height(new_node);
    return new_node;
}

AVLTree::Node* AVLTree::left_rotate(Node* node) {
    Node* new_node = node->right;
    node->right = new_node->left;
    new_node->left = node;
    node->height = update_height(node);
    new_node->height = update_height(new_node);
    return new_node;
}

AVLTree::Node* AVLTree::balance(Node* node) {
    if (get_balance(node) == 2) {
        if (get_balance(node->left) >= 0) {
            node = right_rotate(node);
        }
        else {
            node->right = left_rotate(node->right);
            node = right_rotate(node);
        }
    }
    else if (get_balance(node) == -2) {
        if (get_balance(node->right) <= 0) {
            node = left_rotate(node);
        }
        else {
            node->left = right_rotate(node->left);
            node = left_rotate(node);
        }
    }
    return node;
}

AVLTree::Node* AVLTree::insert_node(Node* node, int value) {
    if (node == nullptr) {
        node = new Node(value);
        return node;
    }
    if (node->key > value) {
        node->left = insert_node(node->left, value);
    }
    else {
        node->right = insert_node(node->right, value);
    }
    node->height = update_height(node);
    node = balance(node);
    return node;
}

AVLTree::Node* AVLTree::remove_node(Node* node, int value) {
    if (node == nullptr) {
        return nullptr;
    }
    if (value < node->key) {
        node->left = remove_node(node->left, value);
    }
    else if (value > node->key) {
        node->right = remove_node(node->right, value);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        else if (node->left == nullptr && node->right != nullptr) {
            Node* right_branch = node->right;
            delete node;
            return right_branch;
        }
        else if (node->left != nullptr && node->right == nullptr) {
            Node* left_branch = node->left;
            delete node;
            return left_branch;
        }
        else {
            int new_min = find_min(node->right)->key;
            node->key = new_min;
            node->left = remove_node(node->right, new_min);
        }
    }
    node->height = update_height(node);
    node = balance(node);
    return node;
}

AVLTree::Node* AVLTree::find_min(Node* node) const {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

void AVLTree::in_order(Node* node, std::vector<int>& result) const {
    if (node == nullptr) {
        return;
    }
    in_order(node->left, result);
    result.push_back(node->key);
    in_order(node->right, result);
}

void AVLTree::destroy(Node* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}
