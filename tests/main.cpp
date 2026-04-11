#include "AVLTree.hpp"
#include <iostream>
#include <cassert>

int main()
{
    AVLTree tree{};

    assert(tree.empty());
    assert(tree.size() == 0);

    assert(tree.insert(5));
    assert(!tree.insert(5));
    assert(tree.contains(5));
    assert(!tree.contains(3));

    tree.insert(3);
    tree.insert(7);
    assert(tree.size() == 3);

    auto vals = tree.values();
    assert(vals.size() == 3);
    assert(vals[0] == 3 && vals[1] == 5 && vals[2] == 7);

    assert(tree.remove(5));
    assert(!tree.contains(5));
    assert(tree.size() == 2);

    AVLTree t2;
    for (int i = 0; i < 100; ++i)
    {
        t2.insert(i);
    }
    assert(t2.size() == 100);
    auto sorted = t2.values();
    for (int i = 0; i < 100; ++i)
    {
        assert(sorted[i] == i);
    }
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
