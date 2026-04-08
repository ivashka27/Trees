#include "AVLTree.hpp"

Node::Node(int val) : left_node(nullptr), right_node(nullptr), height(1), value(val) {};

Node::~Node()
{
    delete left_node;
    delete right_node;
    left_node = nullptr;
    right_node = nullptr;
}

AVLTree::~AVLTree()
{
    delete root_Node_;
    root_Node_ = nullptr;
}

std::vector<int> AVLTree::values() const
{
    if (root_Node_ == nullptr)
    {
        return {};
    }
    std::vector<int> vec;
    values(root_Node_, vec);
    return vec;
}
void AVLTree::values(Node *node, std::vector<int> &vec) const
{
    if (node == nullptr)
    {
        return;
    }
    values(node->left_node, vec);
    vec.push_back(node->value);
    values(node->right_node, vec);
}

bool AVLTree::insert(int value)
{
    if (contains(value))
    {
        return false;
    }
    root_Node_ = insert(value, root_Node_);
    return true;
}

Node *AVLTree::insert(int value, Node *node) // logn
{

    if (node == nullptr)
    {
        return new Node(value);
    }
    if (value < node->value)
        node->left_node = insert(value, node->left_node);
    else
        node->right_node = insert(value, node->right_node);

    return balance(node);
}

Node *AVLTree::find_min_Node(Node *node)
{
    if (node == nullptr)
        return nullptr;
    Node *min_node = node;
    while (min_node->left_node != nullptr)
    {
        min_node = min_node->left_node;
    }
    return min_node;
}

bool AVLTree::remove(int value)
{
    if (!contains(value))
        return false;
    if (root_Node_ == nullptr)
        return false;
    root_Node_ = remove(value, root_Node_);
    return true;
}

Node *AVLTree::remove(int value, Node *node) // возвращает узел, на который должен ссылаться родитель
{
    if (node == nullptr)
        return nullptr;
    if (value < node->value)
    {
        node->left_node = remove(value, node->left_node);
    }
    else if (value > node->value)
    {
        node->right_node = remove(value, node->right_node);
    }
    else
    {
        if (node->left_node == nullptr || node->right_node == nullptr)
        {
            Node *temp = (node->left_node == nullptr) ? node->right_node : node->left_node;
            node->left_node = nullptr;
            node->right_node = nullptr;
            delete node;
            return temp;
        }
        else
        {
            Node *min_node = find_min_Node(node->right_node);
            node->value = min_node->value;
            node->right_node = remove(min_node->value, node->right_node);
        }
    }
    return balance(node);
}

bool AVLTree::contains(int value) const
{ // logn
    // return contains(value, root_Node_);
    if (contains(value, root_Node_) == nullptr)
        return false;
    return true;
}

Node *AVLTree::contains(int value, Node *node) const
{
    if (node == nullptr)
    {
        return nullptr;
    }
    else if (value < node->value)
    {
        return contains(value, node->left_node);
    }
    else if (value > node->value)
    {
        return contains(value, node->right_node);
    }
    return node;
}

// Node *AVLTree::contains()

std::size_t AVLTree::size() const
{
    if (root_Node_ == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + size(root_Node_->left_node) + size(root_Node_->right_node);
    }
}

std::size_t AVLTree::size(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + size(node->left_node) + size(node->right_node);
    }
}

// std::size_t AVLTree::calc_height() const
// {
//     return calc_height(root_Node_);
// }

std::size_t AVLTree::update_height(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + std::max(getHeight(node->left_node), getHeight(node->right_node));
    }
}

bool AVLTree::empty() const
{
    if (root_Node_ == nullptr)
    {
        return true;
    }
    return false;
}

Node *AVLTree::leftRotate(Node *x_node)
{
    Node *y_node = x_node->right_node;
    x_node->right_node = y_node->left_node;
    y_node->left_node = x_node;
    x_node->height = update_height(x_node);
    y_node->height = update_height(y_node);
    return y_node;
}

Node *AVLTree::rightRotate(Node *x_node)
{
    Node *y_node = x_node->left_node;
    x_node->left_node = y_node->right_node;
    y_node->right_node = x_node;
    x_node->height = update_height(x_node);
    y_node->height = update_height(y_node);
    return y_node;
}

Node *AVLTree::left_rightRotate(Node *x_node)
{
    Node *y_node = x_node->left_node;

    Node *z_node = leftRotate(y_node);
    x_node->left_node = z_node;

    z_node = rightRotate(x_node);

    return z_node;
}

Node *AVLTree::right_leftRotate(Node *x_node)
{
    Node *y_node = x_node->right_node;

    Node *z_node = rightRotate(y_node);
    x_node->right_node = z_node;

    z_node = leftRotate(x_node);

    return z_node;
}

int AVLTree::getHeight(Node *node) const
{
    if (node == nullptr)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

int AVLTree::balance_factor(Node *node) const
{
    return getHeight(node->left_node) - getHeight(node->right_node);
}

Node *AVLTree::balance(Node *node)
{
    node->height = getHeight(node);
    if (balance_factor(node) == 2 && balance_factor(node->left_node) >= 0)
    {
        return rightRotate(node);
    }
    if (balance_factor(node) == -2 && balance_factor(node->right_node) <= 0)
    {
        return leftRotate(node);
    }
    if (balance_factor(node) == 2 && balance_factor(node->left_node) < 0)
    {
        return left_rightRotate(node);
    }
    if (balance_factor(node) == -2 && balance_factor(node->right_node) > 0)
    {
        return right_leftRotate(node);
    }
    return node;
}
