#include "AVLTree.hpp"
#include <algorithm>


AVLTree::AVLTree() : root(nullptr), tree_size(0) {}

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::deleteTree(Node* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

int AVLTree::getHeight(Node* node) const {
    return node ? node->height : -1;
}

// разница высот левого и правого поддеревьев
int AVLTree::getBalance(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVLTree::updateHeight(Node* node) {
    if (node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }
}

AVLTree::Node* AVLTree::rotateRight(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    
    updateHeight(node);
    updateHeight(newRoot);
    
    return newRoot;
}

AVLTree::Node* AVLTree::rotateLeft(Node* node) {
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    
    updateHeight(node);
    updateHeight(newRoot);
    
    return newRoot;
}

// Балансировка узла
AVLTree::Node* AVLTree::balance(Node* node) {
    if (!node) return nullptr;
    
    updateHeight(node);
    int balance = getBalance(node);
    
    // Левое поддерево тяжелее
    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            // LR случай - левый поворот левого ребенка
            node->left = rotateLeft(node->left);
        }
        // LL случай - правый поворот
        return rotateRight(node);
    }
    
    // Правое поддерево тяжелее
    if (balance < -1) {
        if (getBalance(node->right) > 0) {
            // RL случай - правый поворот правого ребенка
            node->right = rotateRight(node->right);
        }
        // RR случай - левый поворот
        return rotateLeft(node);
    }
    
    return node;
}

// Вставка узла
AVLTree::Node* AVLTree::insertNode(Node* node, int value, bool& inserted) {
    if (!node) {
        inserted = true;
        return new Node(value);
    }
    
    if (value < node->value) {
        node->left = insertNode(node->left, value, inserted);
    } else if (value > node->value) {
        node->right = insertNode(node->right, value, inserted);
    } else {
        inserted = false;
        return node;
    }
    
    return balance(node);
}

// Поиск минимального узла в поддереве
AVLTree::Node* AVLTree::findMin(Node* node) const {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Удаление минимального узла
AVLTree::Node* AVLTree::removeMin(Node* node) {
    if (!node->left) {
        Node* right = node->right;
        delete node;
        return right;
    }
    node->left = removeMin(node->left);
    return balance(node);
}

// Удаление узла
AVLTree::Node* AVLTree::removeNode(Node* node, int value, bool& removed) {
    if (!node) {
        removed = false;
        return nullptr;
    }
    
    if (value < node->value) {
        node->left = removeNode(node->left, value, removed);
    } else if (value > node->value) {
        node->right = removeNode(node->right, value, removed);
    } else {
        removed = true;
        
        if (!node->left) {
            Node* right = node->right;
            delete node;
            return right;
        }
        
        if (!node->right) {
            Node* left = node->left;
            delete node;
            return left;
        }
        
        // Узел имеет двух потомков
        Node* minNode = findMin(node->right);
        node->value = minNode->value;
        node->right = removeMin(node->right);
    }
    
    return balance(node);
}

bool AVLTree::containsNode(Node* node, int value) const {
    if (!node) return false;
    
    if (value < node->value) {
        return containsNode(node->left, value);
    } else if (value > node->value) {
        return containsNode(node->right, value);
    } else {
        return true;
    }
}

// Сбор всех значений в отсортированном порядке
void AVLTree::collectValues(Node* node, std::vector<int>& result) const {
    if (node) {
        collectValues(node->left, result);
        result.push_back(node->value);
        collectValues(node->right, result);
    }
}

bool AVLTree::contains(int value) const {
    return containsNode(root, value);
}

bool AVLTree::insert(int value) {
    bool inserted = false;
    root = insertNode(root, value, inserted);
    if (inserted) {
        tree_size++;
    }
    return inserted;
}

bool AVLTree::remove(int value) {
    bool removed = false;
    root = removeNode(root, value, removed);
    if (removed) {
        tree_size--;
    }
    return removed;
}

std::size_t AVLTree::size() const {
    return tree_size;
}

bool AVLTree::empty() const {
    return tree_size == 0;
}

std::vector<int> AVLTree::values() const {
    std::vector<int> result;
    collectValues(root, result);
    return result;
}