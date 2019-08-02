#include <iostream>
#include "DataLoader.h"

int main() {
    DataLoader loader{"get_x_test.txt"};
    std::cout<<std::boolalpha;
    std::cout << "\n" << loader.getExpressionString() << "\n";
    std::cout << loader.isOpen() << loader.hasCorrectCharacters() << std::endl;
    return 0;
}