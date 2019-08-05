//
// Created by shiro on 02.08.19.
//

#include "PrefixExpression.h"
#include "Node.h"
#include <iostream>
#include <InvalidExpressionError.h>

void PrefixExpression::printInStandard(std::ostream& output) {
    standardPrintHelper(output, root.get());
}

int PrefixExpression::calculate() {
    return calculateHelper(root.get());
}

/*
 * Function uses recursion to construct tree from data in string.
 *
 */
int PrefixExpression::createFromStringHelper(const std::string &expressionString, int index, Node *newNode) {
    int shift{}; //stores number of used character
    int spaces{};

    /*
     * Keeping track of index and spaces before actual numbers is important for
     * future function calls
     */
    while(isspace(expressionString[index]))
    {
        ++index;
        ++spaces;
    }
    /*
     * Check for trailing spaces
     */
    if(index >= expressionString.length())
        throw InvalidExpressionError("Invalid expression");

    /*
     * If string at position index is a operator we branch the tree
     * and expect new branches to close when number or 'x' is spotted
     * in next function calls
     */
    if(isOperator(expressionString[index]))
    {

        newNode->setValue(std::string(1,expressionString[index])); //assign operator to node

        if(index + 1 >= expressionString.length())
            throw InvalidExpressionError("Invalid expression");

        newNode ->setLSon(std::move(std::make_unique<Node>())); //initialize left son


        shift += createFromStringHelper(expressionString, index + 1, newNode->getLSon()) ;

        if(shift + index + 1 >= expressionString.length())
            throw InvalidExpressionError("Invalid expression");

        newNode->setRSon(std::move(std::make_unique<Node>()));  //initialize right son

        shift += createFromStringHelper(expressionString, index + shift + 1, newNode->getRSon());

        return shift + 1 + spaces;  //number of characters used to complete subtree with root in current operator
    }
    else if (expressionString[index]== 'x') //simple code run when x is encountered
    {
        x=true;
        newNode->setValue(std::string(1,expressionString[index]));
        return ++spaces;
    }
    else  //code run when dealing with numbers
    {
        int numDig = 0; //stores how many digits are in number
        while(isdigit(expressionString[index + numDig]))
        {
            ++numDig;
        }
        newNode->setValue(expressionString.substr(index,numDig));
        return numDig + spaces; //number of digits plus eventual spaces before
    }
}

bool PrefixExpression::isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '/') || (c == '*');
}

void PrefixExpression::print(std::ostream& output) {
    if(root==nullptr)
        return;
    printPreorder(output, root.get());
}
/* Given a binary tree, print its nodes in preorder*/
void PrefixExpression::printPreorder(std::ostream& output,Node * node)
{
    if (node == nullptr)
        return;

    /* first print data of node */
    output << node->getValue() << " ";

    /* then recur on left sutree */
    printPreorder(output, node->getLSon());

    /* now recur on right subtree */
    printPreorder(output, node->getRSon());
}

void PrefixExpression::standardPrintHelper(std::ostream& output, Node *node) {

    if (node == nullptr)
        return;
    /* indicates if parentheses were open */
    bool openParentheses{false};

    /*
     * We only need parentheses around child when parent is a higher priority operator
     * thus we are checking this below
     */
    if(node->isHighPriorityOperatorNode())
        if(node->getLSon()->isLowPriorityOperatorNode())
        {
            output<<"( ";
            openParentheses=true;
        }

    /* first recur on left child */
    standardPrintHelper(output, node->getLSon());

    if(openParentheses)
    {
        output<<") ";
        openParentheses=false;
    }
    /* then print the data of node */
    output << node->getValue() << " ";

    /*
     * check for brackets around second child
     */
    if(node->isHighPriorityOperatorNode())
        if(node->getRSon()->isLowPriorityOperatorNode())
        {
            output<<"( ";
            openParentheses=true;
        }
    /* now recur on right child */
    standardPrintHelper(output, node->getRSon());

    if(openParentheses)
    {
        output<<") ";
    }
}

int PrefixExpression::calculateHelper(Node *node) {
    if(node->isOperatorNode())
    {
        if(node->getValue()[0]=='+')
            return calculateHelper(node->getLSon()) + calculateHelper(node -> getRSon());

        if(node->getValue()[0]=='-')
            return calculateHelper(node->getLSon()) - calculateHelper(node -> getRSon());

        if(node->getValue()[0]=='*')
            return calculateHelper(node->getLSon()) * calculateHelper(node -> getRSon());

        if(node->getValue()[0]=='/')
            return calculateHelper(node->getLSon()) / calculateHelper(node -> getRSon());

    } else if (node ->getValue()[0]=='x')
    {
        return xValue;
    }
    else
    {
        return stoi(node->getValue());
    }

    return 0;
}

void PrefixExpression::createFromString(const std::string &expressionString) {
    createFromStringHelper(expressionString, 0, root.get());
}

void PrefixExpression::load(const DataLoader &loader) {
    if(root == nullptr)
        root = std::make_unique<Node>();
    createFromString(loader.getExpressionString());
    xValue = loader.getXValue();

}

void PrefixExpression::setX(int value) {
    xValue = value;
    x = true;


}

void PrefixExpression::simplify() {
    bool simplified{true};
    while(simplified)
    {
        simplified = simplifyHelper(root.get());
    }


}

bool PrefixExpression::hasX() {
    return x;
}

int PrefixExpression::getXValue() const {
    return xValue;
}

bool PrefixExpression::simplifyHelper(Node *node) {
    bool simplified{false};
    if(node == nullptr)
        return simplified;

    if(node->isOperatorNode())
        if(!node->areSonsValueNodes())
        {
            if(node->getLSon()->isOperatorNode())
                simplified = simplifyHelper (node->getLSon());

            if(node->getRSon()->isOperatorNode())
                simplified |= simplifyHelper (node->getRSon());
            return simplified;
        } else
        {
            switch (node->getValue()[0])
            {
                case '+':
                    if(calculateHelper(node->getLSon()) == 0)
                    {
                        node->lSon = nullptr;
                        node->value = node ->getRSon() -> getValue();
                        node->rSon = nullptr;
                        simplified = true;
                        break;
                    }
                    if(calculateHelper(node->getRSon()) == 0)
                    {
                        node->rSon = nullptr;
                        node->value = node ->getLSon() -> getValue();
                        node->lSon = nullptr;
                        simplified = true;
                        break;
                    }
                    break;
                case '-':
                    if(calculateHelper(node->getRSon()) == 0)
                    {
                        node->value = node ->getLSon() -> getValue();
                        node->rSon = nullptr;
                        node->lSon = nullptr;
                        simplified = true;
                        break;
                    }
                    if(calculateHelper(node->getRSon()) == calculateHelper(node->getLSon()))
                    {
                        node->lSon = nullptr;
                        node->value ="0";
                        node->rSon = nullptr;
                        simplified = true;
                        break;

                    }
                    break;
                case '*':
                    if(calculateHelper(node->getLSon()) == 0)
                    {
                        node->lSon = nullptr;
                        node->value = '0';
                        node->rSon = nullptr;
                        simplified = true;
                        break;
                    }
                    if(calculateHelper(node->getRSon()) == 0)
                    {
                        node->lSon = nullptr;
                        node->value ='0';
                        node->rSon = nullptr;
                        simplified = true;
                        break;
                    }
                    if(calculateHelper(node->getLSon()) == 1)
                    {
                        node->lSon = nullptr;
                        node->value = node ->getRSon() -> getValue();
                        node->rSon = nullptr;
                        simplified = true;
                        break;
                    }
                    if(calculateHelper(node->getRSon()) == 1)
                    {

                        node->value = node ->getLSon() -> getValue();
                        node->lSon = nullptr;
                        node->rSon = nullptr;
                        simplified = true;
                        break;
                    }
                    break;
                case '/':
                    if(calculateHelper(node->getLSon()) == 0)
                    {
                        node->lSon = nullptr;
                        node->value = '0';
                        node->rSon = nullptr;
                        simplified = true;
                    }
                    break;

            }
            return simplified;
        }
    return simplified;
}

PrefixExpression::PrefixExpression() = default;

