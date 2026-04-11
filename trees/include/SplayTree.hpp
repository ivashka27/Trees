#pragma once

#include <vector>
#include <cstddef>

class SplayTree
{
public:
    // Запрещаем конструктор копирования и оператор присваивания
    // В задании это явно не требовалось, но без этого возникает проблема:
    // компилятор автоматически сгенерирует поверхностное копирование (просто скопирует указатель root_)
    // В результате два разных объекта SplayTree будут указывать на одну и ту же память
    // При удалении первого дерева память освободится, а второй объект получит висячий указатель
    // При удалении второго дерева произойдёт double free
    // Чтобы этого избежать, нужно либо:
    //   1) Запретить копирование (простой вариант, выбран здесь)
    //   2) Реализовать глубокое копирование (сложный вариант, рекурсивно копировать все узлы) В задании это явно не требовалось
    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~SplayTree();

private:
    struct Node {
        int value;
        Node* left;
        Node* right;
        Node* parent;

        explicit Node(int v) : value(v), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root_ = nullptr;
    std::size_t size_ = 0;

    void rotateLeft(Node* x);
    void rotateRight(Node* x);
    void splay(Node* x);

    Node* findNode(int value) const;
    Node* subtreeMax(Node* node) const;

    void inorderTraversal(Node* node, std::vector<int>& result) const;
    void deleteSubtree(Node* node);

};