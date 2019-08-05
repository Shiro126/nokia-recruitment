#include <iostream>
#include "DataLoader.h"
#include "Node.h"
#include "PrefixExpression.h"
#include "InvalidExpressionError.h"


int main() {

    std::cout << "Please input file name: ";
    std::string fileName;
    std::cin >> fileName;
    try {
        DataLoader loader{fileName};
        std::cout << "\n" << loader.getExpressionString() << "\n";
        PrefixExpression expression{};
        expression.load(loader);
        std::cout << "Expression in prefix notation: ";
        expression.print(std::cout);
        std::cout << "\nExpression in standard notation: ";
        expression.printInStandard(std::cout);
        expression.simplify();
        std::cout << "\nSimplest form of expression: ";
        expression.printInStandard(std::cout);
        std::cout << "\nExpression evaluates to: " << expression.calculate();
        if (expression.hasX())
            std::cout << "\n with x = " << expression.getXValue();


    } catch (InvalidExpressionError& error)
    {
        std::cout<<error.what();
    }

    return 0;
}