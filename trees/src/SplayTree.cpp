#include "SplayTree.hpp"
#include <stack>

// правый поворот
void SplayTree::right_rotate(Node* x) {
    Node* y = x->left; // y - левый ребёнок икса

    // передаем правого ребенка y налево к x
    x->left = y->right;
    if (y->right != nullptr) {
        y->right->parent = x; // обновляем родителя для y (теперь его родитель x)
    }

    // привязываем y к родителю икса
    y->parent = x->parent;
    if (x->parent == nullptr) {
        root = y; // если у икса нет родителя, значит он был корнем, поэтому y становится новым корнем дерева
    } else if (x == x->parent->right) {
        x->parent->right = y; // если x был правым сыном
    } else {
        x->parent->left = y;  // если x был левым сыном
    }

    // смещаем икс вниз, и делаем его родителем y
    y->right = x;
    x->parent = y;
}

// левый поворот (меняем left и right, т. к. всё симметрично)
void SplayTree::left_rotate(Node* x) {
    Node* y = x->right; // y - это правый ребенок, который пойдет наверх

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

// реализуем splaytree, которая и будет поднимать наш икс
void SplayTree::splay(Node* x) {
    if (x == nullptr) return;

    while (x->parent != nullptr) {
        Node* p = x->parent;
        Node* g = p->parent; // Дедушка (может быть nullptr)

        if (g == nullptr) {
            // 1 случай: родитель - корень дерева
            if (x == p->left) {
                right_rotate(p);
            } else {
                left_rotate(p);
            }
        } else if (p->left == x && g->left == p) {
            // 2 случай: оба левые
            right_rotate(g);
            right_rotate(p);
        } else if (p->right == x && g->right == p) {
            // 3 случай: оба правые
            left_rotate(g);
            left_rotate(p);
        } else if (p->right == x && g->left == p) {
            // случай 4: x - правый ребенок, p - левый
            left_rotate(p);
            right_rotate(g);
        } else if (p->left == x && g->right == p) {
            // 5 случай x - левый ребенок, p - правый
            right_rotate(p);
            left_rotate(g);
        }
    }
}

bool SplayTree::insert(int value) {
    // для пустого дерева создаём корень
    if (root == nullptr) {
        root = new Node(value);
        tree_size++;
        return true;
    }

    Node* current = root;
    Node* parent = nullptr;

    // идём вниз
    while (current != nullptr) {
        parent = current;
        if (value == current->value) {
            // если число уже есть, мы не добавляем дубликат, но в корень всё равно поднимаем
            splay(current);
            return false;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // создаем узел и привязываем его к найденному родителю
    Node* new_node = new Node(value);
    new_node->parent = parent;

    if (value < parent->value) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }

    tree_size++;   
    splay(new_node); // поднимаем новый узел
    return true;
}

bool SplayTree::contains(int value) const {
    Node* current = root;
    Node* last = nullptr;

    while (current != nullptr) {
        last = current;
        if (value == current->value) {
            // для найденного убираем const с this и поднимаем узел в корень
            const_cast<SplayTree*>(this)->splay(current);
            return true;
        } else if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // если число не найдено, поднимаем последний узел, до которого смогли дойти
    if (last != nullptr) {
        const_cast<SplayTree*>(this)->splay(last);
    }
    return false;
}

std::size_t SplayTree::size() const {
    return tree_size;
}

bool SplayTree::empty() const {
    return tree_size == 0;
}

// тут делаем цикл для обхода дерева, чтобы извлечь элементы
std::vector<int> SplayTree::values() const {
    std::vector<int> result;
    std::stack<Node*> nodes_stack;
    Node* current = root;

    while (current != nullptr || !nodes_stack.empty()) {
        while (current != nullptr) {
            nodes_stack.push(current);
            current = current->left;
        }
        current = nodes_stack.top();
        nodes_stack.pop();
        result.push_back(current->value);
        current = current->right;
    }

    return result;
}

// удаляем узлы
void SplayTree::clear(Node* node) {
    if (node == nullptr) return;
    clear(node->left); 
    clear(node->right);
    delete node;
}

SplayTree::~SplayTree() {
    clear(root);
}

bool SplayTree::remove(int value) {
    if (root == nullptr) return false;
    if (!contains(value)) {
        return false;
    }
    Node* old_root = root;
    if (root->left == nullptr) {
        // левого поддерева нет => делаем корнем правое
        root = root->right;
        if (root != nullptr) root->parent = nullptr;
    } else {
        // левое поддерево есть
        Node* left_subtree = root->left;
        left_subtree->parent = nullptr; 
        
        Node* max_left = left_subtree;
        while (max_left->right != nullptr) {
            max_left = max_left->right;
        }

        root = left_subtree;
        splay(max_left);

        // прикрепляем старое правое поддерево
        root->right = old_root->right;
        if (root->right != nullptr) {
            root->right->parent = root;
        }
    }

    delete old_root; // ну и чистим
    tree_size--;
    return true;
}