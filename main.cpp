#include <iostream>
#include "DataLoader.h"
#include "Node.h"
#include "PrefixExpression.h"


int main() {

    DataLoader loader{"test.txt"};
    std::cout<<std::boolalpha;
    std::cout << "\n" << loader.getExpressionString() << "\n";
    PrefixExpression expression{loader.getExpressionString()};
    for(int i =0; i<1000000; i++)
        expression.load(loader);
    expression.print();
    std::cout<<"\n";
    expression.printInStandard();
    std::cout<<"\n"<<expression.calculate();
    return 0;
}