#include <iostream>
#include <vector>


struct Node {
    int value;
    Node* left;
    Node* right;
    Node* parent;
    Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
};

class SplayTree {
private:
    mutable Node* root;           // корень дерева 
    std::size_t sz;             // количество узлов

    // Вращение вокруг узла x
    void rotate(Node* x) const {
        Node* p = x->parent;
        if (!p) return;                 // нет родителя – нельзя вращать
        Node* g = p->parent;
        if (p->left == x) {
               //   правый поворот: x поднимается вместо p
            p->left = x->right;
            if (x->right) x->right->parent = p;
            x->right = p;
        } else {
            // левый поворот: x поднимается вместо p
            p->right = x->left;
            if (x->left) x->left->parent = p;
            x->left = p;
        }
        p->parent = x;
        x->parent = g;
        if (g) {
            if (g->left == p) g->left = x;
            else g->right = x;
        } else {

            root = x;
        }
    }

    // splay: поднимает узел x к корню
    void splay(Node* x) const {
        if (!x) return;
        while (x->parent) {
            Node* p = x->parent;
            Node* g = p->parent;
            if (!g) {
                // oдиночное вращение
                rotate(x);
            } else if ((g->left == p && p->left == x) ||
                       (g->right == p && p->right == x)) {
                // двойной поворот в одну сторону
                rotate(p);
                rotate(x);
            } else {
                // 2 поворота в разные стороны
                rotate(x);
                rotate(x);
            }
        }
        
        root = x;
    }

    
    Node* findNode(int value, Node*& parent) const {
        Node* cur = root;
        parent = nullptr;
        while (cur) {
            parent = cur;
            if (value < cur->value) cur = cur->left;
            else if (value > cur->value) cur = cur->right;
            else return cur; 
        }
        return nullptr;
    }

    void inorder(Node* node, std::vector<int>& res) const {
        if (!node) return;
        inorder(node->left, res);
        res.push_back(node->value);
        inorder(node->right, res);
    }

    // удаление всех узлов
    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    SplayTree() : root(nullptr), sz(0) {}

    bool contains(int value) const {
        Node* parent = nullptr;
        Node* node = findNode(value, parent);
        if (node) {
            // если найден, сплеим его
            splay(node);
            return true;
        }
        // если не найден, сплеим последний просмотреный
        if (parent) splay(parent);
        return false;
    }

    bool insert(int value) {
        if (!root) {
            // если пустое дерево, тогда новый узел становится корнем
            root = new Node(value);
            sz = 1;
            return true;
        }
        Node* parent = nullptr;
        Node* node = findNode(value, parent);
        if (node) {
            // уже есть такой элемент – сплеим его и ничего не вставляем
            splay(node);
            return false;
        }
        // создаём новый узел и подвешиваем к parent
        Node* newNode = new Node(value);
        newNode->parent = parent;
        if (value < parent->value) parent->left = newNode;
        else parent->right = newNode;
        // эоднимаем вставленный узел в корень
        splay(newNode);
        sz++;
        return true;
    }

    bool remove(int value) {
        Node* parent = nullptr;
        Node* node = findNode(value, parent);
        if (!node) {
            // элемент не найден – сплеим последний просмотренный узел (если есть)
            if (parent) splay(parent);
            return false;
        }
        // сплеим удаляемый узел в корень
        splay(node);
        //   разделяем на левое и правое поддеревья
        Node* L = node->left;
        Node* R = node->right;
        if (L) L->parent = nullptr;
        if (R) R->parent = nullptr;
        // у даляем сам узел
        delete node;
        sz--;
        
        if (!L) {
            //     левое поддерево пусто – корнем становится правое
            root = R;
        } else {
            //   находим максимальный узел в левом поддереве
            root = L;
            Node* maxNode = L;
            while (maxNode->right) maxNode = maxNode->right;
            // поднимаем его в корень и присоединяем правое поддерево
            splay(maxNode);
            root->right = R;
            if (R) R->parent = root;
        }
        return true;
    }


    std::size_t size() const { return sz; }
    bool empty() const { return sz == 0; }

    // возвращает вектор значений в порядке возрастаниf
    std::vector<int> values() const {
        std::vector<int> res;
        inorder(root, res);
        return res;
    }

    ~SplayTree() {
        destroy(root);
    }
};


int main() {
    SplayTree tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    
    std::cout << tree.contains(10) << std::endl;
    std::cout << tree.contains(7) << std::endl;
    
    auto vals = tree.values();
    for (int x : vals) std::cout << x << " ";
    std::cout << std::endl;
    
    tree.remove(10);
    
    vals = tree.values();
    for (int x : vals) std::cout << x << " ";
    std::cout << std::endl;
    
    return 0;
}
