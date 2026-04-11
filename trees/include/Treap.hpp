#pragma "once"

#include <vector>

struct Node;

class Treap
{
public:
    bool contains(int value) const;
    bool insert(int value);
    bool remove(int value);

    std::size_t size() const;
    bool empty() const;

    std::vector<int> values() const;

    ~Treap();

private:
    Node*       root_ = nullptr;
    std::size_t sz_   = 0;
};