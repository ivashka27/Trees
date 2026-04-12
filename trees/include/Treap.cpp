#include "Treap.hpp"
#include <cstdlib>
#include <ctime>

// Простой генератор случайных приоритетов
static int random_priority()
{
    static bool seeded = false;
    if (!seeded)
    {
        srand(time(nullptr));
        seeded = true;
    }
    return rand();
}

Treap::Node::Node(int k)
    : key(k), priority(random_priority()), left(nullptr), right(nullptr)
{
}

Treap::Treap() : root(nullptr), count(0) {}

Treap::~Treap()
{
    clear(root);
}

void Treap::clear(Node *t)
{
    if (!t)
        return;
    clear(t->left);
    clear(t->right);
    delete t;
}

bool Treap::contains(int value) const
{
    Node *cur = root;
    while (cur)
    {
        if (value == cur->key)
            return true;
        if (value < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }
    return false;
}

Treap::Node *Treap::merge(Node *L, Node *R)
{
    if (!L)
        return R;
    if (!R)
        return L;
    if (L->priority > R->priority)
    {
        L->right = merge(L->right, R);
        return L;
    }
    else
    {
        R->left = merge(L, R->left);
        return R;
    }
}

void Treap::split(Node *t, int key, Node *&L, Node *&R)
{
    if (!t)
    {
        L = R = nullptr;
        return;
    }
    if (t->key < key)
    {
        split(t->right, key, t->right, R);
        L = t;
    }
    else
    {
        split(t->left, key, L, t->left);
        R = t;
    }
}

bool Treap::insert(int value)
{
    if (contains(value))
        return false;
    Node *newNode = new Node(value);
    Node *L = nullptr, *R = nullptr;
    split(root, value, L, R);
    root = merge(merge(L, newNode), R);
    ++count;
    return true;
}

bool Treap::remove(int value)
{
    if (!contains(value))
        return false;
    Node *L = nullptr, *M = nullptr, *R = nullptr;
    split(root, value, L, M);
    split(M, value + 1, M, R);
    delete M;
    root = merge(L, R);
    --count;
    return true;
}

std::size_t Treap::size() const
{
    return count;
}

bool Treap::empty() const
{
    return count == 0;
}

void Treap::inorder(Node *t, std::vector<int> &v) const
{
    if (!t)
        return;
    inorder(t->left, v);
    v.push_back(t->key);
    inorder(t->right, v);
}

std::vector<int> Treap::values() const
{
    std::vector<int> res;
    inorder(root, res);
    return res;
}
