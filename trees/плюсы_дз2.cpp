

#include <iostream>
#pragma once
#include <vector>

int main() {
    class SplayTree {
        struct Node {
            int v;
            Node* l, * r, * p;
            Node(int x) : v(x), l(nullptr), r(nullptr), p(nullptr) {}
        };

        Node* root = nullptr;
        size_t sz = 0;

        void rotL(Node* x) {
            Node* p = x->p;
            if (!p) return;
            Node* g = p->p;

            p->r = x->l;
            if (x->l) x->l->p = p;

            x->l = p;
            p->p = x;

            x->p = g;

            if (g) {
                if (g->l == p) g->l = x;
                else g->r = x;
            }
            else root = x;
        }

        void rotR(Node* x) {
            Node* p = x->p;
            if (!p) return;
            Node* g = p->p;

            p->l = x->r;
            if (x->r) x->r->p = p;

            x->r = p;
            p->p = x;

            x->p = g;

            if (g) {
                if (g->l == p) g->l = x;
                else g->r = x;
            }
            else root = x;
        }

        void splay(Node* x) {
            while (x->p) {
                Node* p = x->p;
                Node* g = p->p;

                if (!g) {
                    if (p->l == x) rotR(x);
                    else rotL(x);
                }
                else if (g->l == p && p->l == x) {
                    rotR(p);
                    rotR(x);
                }
                else if (g->r == p && p->r == x) {
                    rotL(p);
                    rotL(x);
                }
                else {
                    if (p->l == x) {
                        rotR(x);
                        rotL(x);
                    }
                    else {
                        rotL(x);
                        rotR(x);
                    }
                }
            }
        }

        Node* find(int x) const {
            Node* cur = root;
            Node* last = nullptr;
            while (cur) {
                last = cur;
                if (x == cur->v) return cur;
                if (x < cur->v) cur = cur->l;
                else cur = cur->r;
            }
            return last;
        }

        void inorder(Node* n, std::vector<int>& a) const {
            if (!n) return;
            inorder(n->l, a);
            a.push_back(n->v);
            inorder(n->r, a);
        }

        void clear(Node* n) {
            if (!n) return;
            clear(n->l);
            clear(n->r);
            delete n;
        }

    public:
        bool contains(int x) const {
            if (!root) return false;
            Node* n = find(x);
            if (!n) return false;
            const_cast<SplayTree*>(this)->splay(n);
            return n->v == x;
        }

        bool insert(int x) {
            if (!root) {
                root = new Node(x);
                sz = 1;
                return true;
            }

            Node* cur = root;
            Node* p = nullptr;

            while (cur) {
                p = cur;
                if (x == cur->v) {
                    splay(cur);
                    return false;
                }
                if (x < cur->v) cur = cur->l;
                else cur = cur->r;
            }

            Node* n = new Node(x);
            n->p = p;

            if (x < p->v) p->l = n;
            else p->r = n;

            splay(n);
            sz++;
            return true;
        }

        bool remove(int x) {
            if (!root) return false;

            Node* n = find(x);
            if (!n || n->v != x) {
                if (n) splay(n);
                return false;
            }

            splay(n);

            Node* L = n->l;
            Node* R = n->r;

            if (L) L->p = nullptr;
            if (R) R->p = nullptr;

            delete n;
            sz--;

            if (!L) {
                root = R;
            }
            else {
                Node* m = L;
                while (m->r) m = m->r;

                root = L;
                splay(m);

                root->r = R;
                if (R) R->p = root;
            }

            return true;
        }

        size_t size() const {
            return sz;
        }

        bool empty() const {
            return sz == 0;
        }

        std::vector<int> values() const {
            std::vector<int> res;
            inorder(root, res);
            return res;
        }

        ~SplayTree() {
            clear(root);
        }
    };
}