#include "SplayTree.hpp"

struct SplayTree::Node
{
    explicit Node(int value_arg)
        : value(value_arg)
    {
    }

    int value;
    Node* left = nullptr;
    Node* right = nullptr;
};

bool SplayTree::contains(int value) const
{
    if (root_ == nullptr)
    {
        return false;
    }

    // После поиска стараемся поднять нужный узел ближе к корню.
    root_ = splay(root_, value);
    return root_->value == value;
}

bool SplayTree::insert(int value)
{
    if (root_ == nullptr)
    {
        root_ = new Node(value);
        ++size_;
        return true;
    }

    // Сначала подтягиваем к корню либо сам элемент, либо ближайший к нему узел.
    root_ = splay(root_, value);
    if (root_->value == value)
    {
        return false;
    }

    Node* node = new Node(value);
    if (value < root_->value)
    {
        // Новый узел становится корнем, а старый корень уходит вправо.
        node->left = root_->left;
        node->right = root_;
        root_->left = nullptr;
    }
    else
    {
        // Здесь всё симметрично старый корень уходит влево.
        node->right = root_->right;
        node->left = root_;
        root_->right = nullptr;
    }

    root_ = node;
    ++size_;
    return true;
}

bool SplayTree::remove(int value)
{
    if (root_ == nullptr)
    {
        return false;
    }

    root_ = splay(root_, value);
    if (root_->value != value)
    {
        return false;
    }

    // После splay нужный элемент должен оказаться в корне.
    Node* node_to_delete = root_;
    if (root_->left == nullptr)
    {
        root_ = root_->right;
    }
    else
    {
        Node* right_subtree = root_->right;
        // В левом поддереве поднимаем самый большой элемент наверх.
        // После этого к нему удобно присоединить правое поддерево.
        root_ = splay(root_->left, value);
        root_->right = right_subtree;
    }

    delete node_to_delete;
    --size_;
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
    std::vector<int> result;
    result.reserve(size_);
    // Обход слева направо даёт элементы в отсортированном порядке.
    inorder(root_, result);
    return result;
}

SplayTree::~SplayTree()
{
    clear(root_);
}

SplayTree::Node* SplayTree::rotateRight(Node* node)
{
    // Малый правый поворот вокруг node.
    Node* new_root = node->left;
    node->left = new_root->right;
    new_root->right = node;
    return new_root;
}

SplayTree::Node* SplayTree::rotateLeft(Node* node)
{
    // Малый левый поворот вокруг node.
    Node* new_root = node->right;
    node->right = new_root->left;
    new_root->left = node;
    return new_root;
}

SplayTree::Node* SplayTree::splay(Node* node, int value)
{
    // Эта функция старается поднять нужное значение к корню.
    // Если точного значения нет, наверху окажется ближайший посещённый узел.
    if (node == nullptr || node->value == value)
    {
        return node;
    }

    if (value < node->value)
    {
        if (node->left == nullptr)
        {
            return node;
        }

        if (value < node->left->value)
        {
            // Случай zig-zig идём два раза влево.
            node->left->left = splay(node->left->left, value);
            node = rotateRight(node);
        }
        else if (value > node->left->value)
        {
            // Случай zig-zag сначала влево, потом вправо.
            node->left->right = splay(node->left->right, value);
            if (node->left->right != nullptr)
            {
                node->left = rotateLeft(node->left);
            }
        }

        return node->left == nullptr ? node : rotateRight(node);
    }

    if (node->right == nullptr)
    {
        return node;
    }

    if (value > node->right->value)
    {
        // Случай zag-zag идём два раза вправо.
        node->right->right = splay(node->right->right, value);
        node = rotateLeft(node);
    }
    else if (value < node->right->value)
    {
        // Случай zag-zig сначала вправо, потом влево.
        node->right->left = splay(node->right->left, value);
        if (node->right->left != nullptr)
        {
            node->right = rotateRight(node->right);
        }
    }

    return node->right == nullptr ? node : rotateLeft(node);
}

void SplayTree::inorder(const Node* node, std::vector<int>& result)
{
    if (node == nullptr)
    {
        return;
    }

    // Обходим левое поддерево, потом текущий узел, потом правое.
    inorder(node->left, result);
    result.push_back(node->value);
    inorder(node->right, result);
}

void SplayTree::clear(Node* node)
{
    if (node == nullptr)
    {
        return;
    }

    // Освобождаем дерево снизу вверх, чтобы не потерять потомков.
    clear(node->left);
    clear(node->right);
    delete node;
}
