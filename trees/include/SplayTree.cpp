#include "SplayTree.hpp"
#include <cstddef>
#include <vector>

class SplayTree {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    std::size_t tree_size;


    void rotateLeft(Node* x) {
        Node* y = x->right;
        if (!y) return;

        x->right = y->left;
        if (y->left) y->left->parent = x;

        y->parent = x->parent;
        if (!x->parent) {
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

    void rotateRight(Node* x) {
        Node* y = x->left;
        if (!y) return;

        x->left = y->right;
        if (y->right) y->right->parent = x;

        y->parent = x->parent;
        if (!x->parent) {
            root = y;
        }
        else if (x == x->parent->left) {
            x->parent->left = y;
        }
        else {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }

    void splay(Node* x) {
        while (x->parent) {
            Node* p = x->parent;
            Node* g = p->parent;

            if (!g) {
                // Zig - îäèí ïîâîðîò
                if (x == p->left) {
                    rotateRight(p);
                }
                else {
                    rotateLeft(p);
                }
            }
            else if (x == p->left && p == g->left) {
                // Zig-zig - äâà ïðàâûõ ïîâîðîòà
                rotateRight(g);
                rotateRight(p);
            }
            else if (x == p->right && p == g->right) {
                // Zig-zig - äâà ëåâûõ ïîâîðîòà
                rotateLeft(g);
                rotateLeft(p);
            }
            else if (x == p->right && p == g->left) {
                // Zig-zag - ëåâûé çàòåì ïðàâûé ïîâîðîò
                rotateLeft(p);
                rotateRight(g);
            }
            else {
                // Zig-zag - ïðàâûé çàòåì ëåâûé ïîâîðîò
                rotateRight(p);
                rotateLeft(g);
            }
        }
    }

    Node* findNode(int value) const {
        Node* current = root;
        Node* last = nullptr;

        while (current) {
            last = current;
            if (value == current->value) {
                const_cast<SplayTree*>(this)->splay(current);
                return current;
            }
            else if (value < current->value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        if (last) {
            const_cast<SplayTree*>(this)->splay(last);
        }
        return nullptr;
    }

    Node* findMax(Node* node) {
        while (node->right) {
            node = node->right;
        }
        return node;
    }

    void collectValues(Node* node, std::vector<int>& result) const {
        if (!node) return;
        collectValues(node->left, result);
        result.push_back(node->value);
        collectValues(node->right, result);
    }

    void clearTree(Node* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    SplayTree() : root(nullptr), tree_size(0) {}

    ~SplayTree() {
        clearTree(root);
    }

    bool contains(int value) const {
        return findNode(value) != nullptr;
    }

    bool insert(int value) {
        if (!root) {
            root = new Node(value);
            tree_size++;
            return true;
        }

        Node* current = root;
        Node* parent = nullptr;

        while (current) {
            parent = current;
            if (value == current->value) {
                splay(current);
                return false;
            }
            else if (value < current->value) {
                current = current->left;
            }
            else {
                current = current->right;
            }
        }

        Node* newNode = new Node(value);
        newNode->parent = parent;

        if (value < parent->value) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }

        splay(newNode);
        tree_size++;
        return true;
    }

    bool remove(int value) {
        Node* node = findNode(value);
        if (!node) return false;

        splay(node);

        Node* leftSubtree = node->left;
        Node* rightSubtree = node->right;

        if (leftSubtree) leftSubtree->parent = nullptr;
        if (rightSubtree) rightSubtree->parent = nullptr;

        delete node;

        if (!leftSubtree) {
            root = rightSubtree;
        }
        else {
            Node* maxLeft = findMax(leftSubtree);
            splay(maxLeft);
            maxLeft->right = rightSubtree;
            if (rightSubtree) rightSubtree->parent = maxLeft;
            root = maxLeft;
        }

        tree_size--;
        return true;
    }

    std::size_t size() const {
        return tree_size;
    }

    bool empty() const {
        return tree_size == 0;
    }

    std::vector<int> values() const {
        std::vector<int> result;
        collectValues(root, result);
        return result;
    }
};
