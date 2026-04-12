#pragma once

#include <vector>
#include <cstddef> // Для std::size_t

class SplayTree
{
public:
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
        Node* parent; // указатель на предка

        // конструктор создания узлов
        Node(int val) : value(val), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root = nullptr; // корень дерева
    std::size_t tree_size = 0;  // счетчик элементов (для метода size())

    // функции поворота
    void left_rotate(Node* x);
    void right_rotate(Node* x);
    void splay(Node* x);
    
    // функция удаления
    void clear(Node* node); 
};