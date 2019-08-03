#include <iostream>
#include "DataLoader.h"
#include "Node.h"
#include "PrefixExpression.h"


int main() {

    DataLoader loader{"test.txt"};
    std::cout<<std::boolalpha;
    std::cout << "\n" << loader.getExpressionString() << "\n";
    std::cout << loader.isOpen() << loader.hasCorrectCharacters() << std::endl;
    PrefixExpression expression{loader.getExpressionString()};
    expression.print();
    std::cout<<"\n";
    expression.printInStandard();
    std::cout<<"\n"<<expression.calculate();
    return 0;
}