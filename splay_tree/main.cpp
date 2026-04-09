#include <iostream>
#include "include/SplayTree.hpp"

int main() {
    SplayTree t;

    t.insert(10);
    t.insert(5);
    t.insert(15);

    t.contains(5);
    t.remove(10);

    for (int x : t.values())
        std::cout << x << " ";

    std::cout << std::endl;
}
