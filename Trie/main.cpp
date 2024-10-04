#include "trie.h"
#include <iostream>

int main() {
    Trie trie;
    bool found = trie.Insert("key1", 10);
    if (found) {
        std::cout << "Key1 inserted successfully" << std::endl;
    } else {
        std::cout << "Key1 already exists" << std::endl;
    }

    return 0;
}
