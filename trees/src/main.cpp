#include <cassert>
#include "AVLTree.hpp"

int main()
{
    AVLTree tree;

    std::cout << "Empty: " << tree.empty()<< std::endl;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(15);

    std::cout << "Empty: " << tree.empty()  << std::endl;
    std::cout << "Size: " << tree.size()  << std::endl;
    std::cout << "Contains 15: " << tree.contains(15)  << std::endl;
    std::cout << "Contains 100: " << tree.contains(100)  << std::endl;

    std::vector<int> vals = tree.values();
    std::cout << "Values: ";
    for (int v : vals)
    {
        std::cout << v << " ";
    }

    std::cout << "Remove 10: " << tree.remove(10)  << std::endl;
    std::cout << "Size: " << tree.size()  << std::endl;
    std::cout << "Contains 10: " << tree.contains(10) << std::endl;

    return 0;
}
