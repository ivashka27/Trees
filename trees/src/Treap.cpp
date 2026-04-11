#include "../include/Treap.hpp"

#include <vector>
#include <cstddef>
#include <cstdlib>
#include <unordered_map>

namespace 
{
    struct Node {
        int value, priority;
        Node* left = nullptr;
        Node* right = nullptr;
    };

    struct State
    {
        Node* root = nullptr;
        std::size_t size = 0;
    };

    std::unordered_map<const Treap*, State> states;

    int get_priority()
    {
        return std::rand();
    }
    
    void split(Node* root, int value, Node*& left, Node*& right)
    {
        if (root == nullptr)
        {
            left = nullptr;
            right = nullptr;
            return;
        }
        if (root->value < value)
        {
            split(root->right, value, root->right, right);
            left = root;
        }
        else
        {
            split(root->left, value, left, root->left);
            right = root;
        }
    }

    Node* merge(Node* left, Node* right)
    {
        if (left == nullptr)
        {
            return right;
        }
        if (right == nullptr)
        {
            return left;
        }
        if (left->priority > right->priority)
        {
            left->right = merge(left->right, right);
            return left;
        }
        else
        {
            right->left = merge(left, right->left);
            return right;
        }
    }
}

bool Treap::contains(int value) const
{
    auto it = states.find(this);
    if (it == states.end())
    {
        return false;
    }

    Node* current = it->second.root;

    while (current != nullptr)
    {
        if (value < current->value)
        {
            current = current->left;
        }
        else if (value > current->value)
        {
            current = current->right;
        }
        else
        {
            return true;
        }
    }

    return false;
}

bool Treap::insert(int value)
{
    State& st = states[this];

    if (contains(value))
    {
        return false;
    }

    Node* left = nullptr;
    Node* right = nullptr;
    split(st.root, value, left, right);

    Node* node = new Node;
    node->value = value;
    node->priority = get_priority();
    node->left = nullptr;
    node->right = nullptr;

    st.root = merge(merge(left,node), right);
    st.size++;

    return true;
}

bool Treap::remove(int value)
{
    auto it = states.find(this);
    if (it == states.end())
    {
        return false;
    }

    State& st = it->second;
    Node* current = st.root;
    Node* parent = nullptr;
    
    while (current != nullptr && current->value != value)
    {
        parent = current;
        if (value < current->value)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
    }

    if (current == nullptr)
    {
        return false;
    }

    Node* merged = merge(current->left, current->right);

    if (parent == nullptr)
    {
        st.root = merged;
    }
    else if(parent->left == current)
    {
        parent->left = merged;
    }
    else
    {
        parent->right = merged;
    }

    delete current;
    st.size--;
    
    return true;
}

std::size_t Treap::size() const
{
    auto it = states.find(this);
    if (it == states.end())
    {
        return 0;
    }
    return it->second.size;
}

bool Treap::empty() const
{
    return size() == 0;
}

std::vector<int> Treap::values() const
{
    std::vector<int> result;

    auto it = states.find(this);
    if (it == states.end())
    {
        return result;
    }

    Node* current = it->second.root;
    std::vector<Node*> st;

    while (current != nullptr || !st.empty())
    {
        while (current != nullptr)
        {
            st.push_back(current);
            current = current->left;
        }

        current = st.back();
        st.pop_back();

        result.push_back(current->value);
        current = current->right;
    }

    return result;
}


Treap::~Treap()
{
    auto it = states.find(this);
    if (it == states.end())
    {
        return;
    }
    
    std::vector<Node*> st;
    if (it->second.root != nullptr)
    {
        st.push_back(it->second.root);
    }

    while (!st.empty())
    {
        Node* current = st.back();
        st.pop_back();

        if (current->left != nullptr)
        {
            st.push_back(current->left);
        }
        if (current->right != nullptr)
        {
            st.push_back(current->right);
        }

        delete current;
    }

    states.erase(it);
}
