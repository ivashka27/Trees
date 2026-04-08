#include <iostream>
#include "AVLTree.h"

int main() {
    AVLTree t;

    std::cout << "Insert:\n";
    std::cout << t.insert(10) << "\n"; 
    std::cout << t.insert(5) << "\n";  
    std::cout << t.insert(15) << "\n"; 
    std::cout << t.insert(7) << "\n";  
    std::cout << t.insert(10) << "\n"; 

    std::cout << "Size: " << t.size() << "\n"; 

    std::cout << "Contains 7: " << t.contains(7) << "\n";   
    std::cout << "Contains 100: " << t.contains(100) << "\n";

    std::cout << "Values: ";
    for (int x : t.values()) {
        std::cout << x << " ";
    }
    std::cout << "\n"; 

    std::cout << "Remove 10: " << t.remove(10) << "\n"; // 1
    std::cout << "Remove 100: " << t.remove(100) << "\n"; // 0

    std::cout << "Values after remove: ";
    for (int x : t.values()) {
        std::cout << x << " ";
    }
    std::cout << "\n"; 

    std::cout << "Size: " << t.size() << "\n";

    std::cout << "Empty: " << t.empty() << "\n";

    t.remove(5);
    t.remove(7);
    t.remove(15);

    std::cout << "Empty after clear: " << t.empty() << "\n"; // 1

    return 0;
}