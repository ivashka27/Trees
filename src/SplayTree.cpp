#include "SplayTree.hpp"

#include <vector>

SplayTree::Node *SplayTree::findForAccess(int value, bool *found)
{
    *found = false;
    Node *cur = root_;
    Node *last = nullptr;
    while (cur != nullptr) {
        last = cur;
        if (value == cur->key) {
            *found = true;
            return cur;
        }
        cur = value < cur->key ? cur->left : cur->right;
    }
    return last;
}

void SplayTree::bringUp(Node *x)
{
    Node *p = x->parent;
    if (p == nullptr) {
        return;
    }
    Node *g = p->parent;
    const bool xIsLeft = (p->left == x);

    if (xIsLeft) {
        p->left = x->right;
        if (x->right != nullptr) {
            x->right->parent = p;
        }
        x->right = p;
    } else {
        p->right = x->left;
        if (x->left != nullptr) {
            x->left->parent = p;
        }
        x->left = p;
    }
    p->parent = x;
    x->parent = g;
    if (g != nullptr) {
        if (g->left == p) {
            g->left = x;
        } else {
            g->right = x;
        }
    } else {
        root_ = x;
    }
}

void SplayTree::splay(Node *x)
{
    if (x == nullptr) {
        return;
    }
    while (x->parent != nullptr) {
        Node *p = x->parent;
        Node *g = p->parent;
        if (g == nullptr) {
            bringUp(x);
        } else {
            const bool xLeft = (p->left == x);
            const bool pLeft = (g->left == p);
            if (xLeft == pLeft) {
                bringUp(p);
                bringUp(x);
            } else {
                bringUp(x);
                bringUp(x);
            }
        }
    }
}

SplayTree::Node *SplayTree::merge(Node *left, Node *right)
{
    if (left == nullptr) {
        return right;
    }
    if (right == nullptr) {
        return left;
    }
    root_ = left;
    Node *m = left;
    while (m->right != nullptr) {
        m = m->right;
    }
    splay(m);
    m->right = right;
    right->parent = m;
    return m;
}

void SplayTree::destroySubtree(Node *n)
{
    if (n == nullptr) {
        return;
    }
    destroySubtree(n->left);
    destroySubtree(n->right);
    delete n;
}

bool SplayTree::contains(int value) const
{
    SplayTree *self = const_cast<SplayTree *>(this);
    bool found = false;
    Node *last = self->findForAccess(value, &found);
    if (last != nullptr) {
        self->splay(last);
    }
    return found;
}

bool SplayTree::insert(int value)
{
    bool found = false;
    Node *last = findForAccess(value, &found);
    if (found) {
        splay(last);
        return false;
    }
    Node *n = new Node{value};
    if (last == nullptr) {
        root_ = n;
    } else if (value < last->key) {
        last->left = n;
        n->parent = last;
    } else {
        last->right = n;
        n->parent = last;
    }
    ++size_;
    splay(n);
    return true;
}

bool SplayTree::remove(int value)
{
    bool found = false;
    Node *last = findForAccess(value, &found);
    if (last == nullptr) {
        return false;
    }
    splay(last);
    if (!found || root_->key != value) {
        return false;
    }

    Node *L = root_->left;
    Node *R = root_->right;
    if (L != nullptr) {
        L->parent = nullptr;
    }
    if (R != nullptr) {
        R->parent = nullptr;
    }
    delete root_;
    --size_;
    root_ = merge(L, R);
    return true;
}

std::size_t SplayTree::size() const
{
    return size_;
}

bool SplayTree::empty() const
{
    return size_ == 0;
}

std::vector<int> SplayTree::values() const
{
    std::vector<int> out;
    if (root_ == nullptr) {
        return out;
    }
    std::vector<const Node *> stack;
    const Node *cur = root_;
    while (cur != nullptr || !stack.empty()) {
        while (cur != nullptr) {
            stack.push_back(cur);
            cur = cur->left;
        }
        cur = stack.back();
        stack.pop_back();
        out.push_back(cur->key);
        cur = cur->right;
    }
    return out;
}

SplayTree::~SplayTree()
{
    destroySubtree(root_);
    root_ = nullptr;
    size_ = 0;
}
