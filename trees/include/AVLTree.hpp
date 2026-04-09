#pragma "once"

#include <vector>

class AVLTree
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~AVLTree();
private:
    std::size_t tree_size = 0;
    
    struct node
    {
        int key;
        unsigned int height;
        node* left;
        node* right;
        node(int k) {key = k; left=right=0; height = 1;}
    };
    node* root = nullptr;
    unsigned int get_h(node* p) const; //высота поддерева для узла p
    int bfactor(node* p) const; //баланс фактор узла p

    void fixheight(node* p); //восстановление корректного значения поля height

    //повороты
    node* rotate_r(node* p);
    node* rotate_l(node* q);

    //балансировка
    node* balance(node* p);

    node* insert(node* p, int k); //вставка ключа k в дерево с корнем p

    node* findmin(node* p); //поиск узла с минимальным ключом из дерева p
    node* removemin(node* p); //удаление узла с мин ключом из p

    node* remove(node* p, int k); //удаление ключа k из дерева p
    void clear(node* p); //удаление всего дерева
    
    void in_order(node* p, std::vector<int>& values) const;
};