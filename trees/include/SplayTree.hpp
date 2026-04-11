#pragma once

#include <vector>
#include <cstddef>

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
    struct Node
    {
        int key;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr;

        explicit Node(int k) : key(k) {}
    };

    Node *root_ = nullptr;
    std::size_t size_ = 0;

    void rotateLeft(Node *p)
    {
        Node *x = p->right;
        Node *par = p->parent;

        p->right = x->left;
        if (x->left)
            x->left->parent = p;

        x->left = p;
        p->parent = x;
        x->parent = par;

        if (par)
        {
            if (par->left == p)
                par->left = x;
            else
                par->right = x;
        }
        else
        {
            root_ = x;
        }
    }

    void rotateRight(Node *p)
    {
        Node *x = p->left;
        Node *par = p->parent;

        p->left = x->right;
        if (x->right)
            x->right->parent = p;

        x->right = p;
        p->parent = x;
        x->parent = par;

        if (par)
        {
            if (par->left == p)
                par->left = x;
            else
                par->right = x;
        }
        else
        {
            root_ = x;
        }
    }

    void splay(Node *x)
    {
        while (x->parent)
        {
            Node *p = x->parent;
            Node *g = p->parent;

            if (!g)
            {
                // Zig
                if (p->left == x)
                    rotateRight(p);
                else
                    rotateLeft(p);
            }
            else if (g->left == p && p->left == x)
            {
                rotateRight(g);
                rotateRight(p);
            }
            else if (g->right == p && p->right == x)
            {
                rotateLeft(g);
                rotateLeft(p);
            }
            else if (g->left == p && p->right == x)
            {
                rotateLeft(p);
                rotateRight(g);
            }
            else
            {
                rotateRight(p);
                rotateLeft(g);
            }
        }
        root_ = x;
    }

    Node *findNode(int key) const
    {
        Node *cur = root_;
        Node *last = nullptr;
        while (cur)
        {
            last = cur;
            if (key < cur->key)
                cur = cur->left;
            else if (key > cur->key)
                cur = cur->right;
            else
                return cur;
        }
        return last;
    }

    static void inorder(Node *node, std::vector<int> &out)
    {
        if (!node)
            return;
        inorder(node->left, out);
        out.push_back(node->key);
        inorder(node->right, out);
    }

    static void destroy(Node *node)
    {
        if (!node)
            return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
};

inline bool SplayTree::contains(int value) const
{
    Node *cur = root_;
    while (cur)
    {
        if (value < cur->key)
            cur = cur->left;
        else if (value > cur->key)
            cur = cur->right;
        else
            return true;
    }
    return false;
}

inline bool SplayTree::insert(int value)
{
    if (!root_)
    {
        root_ = new Node(value);
        ++size_;
        return true;
    }

    Node *near = findNode(value);
    splay(near);

    if (root_->key == value)
        return false;
    Node *n = new Node(value);

    if (value < root_->key)
    {
        n->right = root_;
        n->left = root_->left;
        if (root_->left)
            root_->left->parent = n;
        root_->left = nullptr;
        root_->parent = n;
    }
    else
    {
        n->left = root_;
        n->right = root_->right;
        if (root_->right)
            root_->right->parent = n;
        root_->right = nullptr;
        root_->parent = n;
    }

    root_ = n;
    ++size_;
    return true;
}

inline bool SplayTree::remove(int value)
{
    if (!root_)
        return false;

    Node *target = findNode(value);
    splay(target);

    if (root_->key != value)
        return false;

    Node *old = root_;

    if (!root_->left)
    {
        root_ = root_->right;
        if (root_)
            root_->parent = nullptr;
    }
    else if (!root_->right)
    {
        root_ = root_->left;
        if (root_)
            root_->parent = nullptr;
    }
    else
    {
        Node *leftTree = root_->left;
        Node *rightTree = root_->right;
        leftTree->parent = nullptr;
        rightTree->parent = nullptr;

        root_ = leftTree;
        Node *maxLeft = leftTree;
        while (maxLeft->right)
            maxLeft = maxLeft->right;
        splay(maxLeft);

        root_->right = rightTree;
        rightTree->parent = root_;
    }

    delete old;
    --size_;
    return true;
}

inline std::size_t SplayTree::size() const
{
    return size_;
}

inline bool SplayTree::empty() const
{
    return size_ == 0;
}

inline std::vector<int> SplayTree::values() const
{
    std::vector<int> result;
    result.reserve(size_);
    inorder(root_, result);
    return result;
}

inline SplayTree::~SplayTree()
{
    destroy(root_);
}
