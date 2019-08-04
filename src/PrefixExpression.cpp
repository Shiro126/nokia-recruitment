//
// Created by shiro on 02.08.19.
//

#include "PrefixExpression.h"
#include "Node.h"
#include <iostream>
#include <InvalidExpressionError.h>

void PrefixExpression::printInStandard() {
    standardPrintHelper(root.get());
}

int PrefixExpression::calculate() {
    return calculateHelper(root.get());
}

/*
 * Function uses recursion to construct tree from data in string.
 *
 */
int PrefixExpression::createFromStringHelper(const std::string &expressionString, int index, Node *newNode) {
    int shift{}; //stores number of spaces

    /*
     * Keeping track of index and spaces before actual numbers is important for
     * future function calls
     */
    while(isspace(expressionString[index]))
    {
        ++index;
        ++shift;
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
        newNode->setValue(std::string(1,expressionString[index]));

        newNode->setRSon(std::move(std::make_unique<Node>()));
        newNode ->setLSon(std::move(std::make_unique<Node>()));

        if(index + 1 >= expressionString.length())
            throw InvalidExpressionError("Invalid expression");

        shift += createFromStringHelper(expressionString, index + 1, newNode->getLSon()) ;

        if(shift + index + 1 >= expressionString.length())
            throw InvalidExpressionError("Invalid expression");

        shift += createFromStringHelper(expressionString, index + shift + 1, newNode->getRSon());

        return shift+1;
    }
    else if (expressionString[index]== 'x')
    {
        newNode->setValue(std::string(1,expressionString[index]));
        return ++shift;
    }
    else
    {
        int numEnd = 0;
        while(isdigit(expressionString[index + numEnd]))
        {
            ++numEnd;
        }
        newNode->setValue(expressionString.substr(index,numEnd));
        return numEnd + shift;
    }
}

bool PrefixExpression::isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '/') || (c == '*');
}

void PrefixExpression::print() {
    if(root==nullptr)
        return;
    printPreorder(root.get());
}
/* Given a binary tree, print its nodes in preorder*/
void PrefixExpression::printPreorder(Node* node)
{
    if (node == nullptr)
        return;

    /* first print data of node */
    std::cout << node->getValue() << " ";

    /* then recur on left sutree */
    printPreorder(node->getLSon());

    /* now recur on right subtree */
    printPreorder(node->getRSon());
}

void PrefixExpression::standardPrintHelper(Node *node) {

    if (node == nullptr)
        return;
    bool openParenthesis{false};
    if(node->isHighPriorityOperatorNode())
        if(node->getLSon()->isLowPriorityOperatorNode())
        {
            std::cout<<"( ";
            openParenthesis=true;
        }

    /* first recur on left child */
    standardPrintHelper(node->getLSon());

    if(openParenthesis)
    {
        std::cout<<") ";
        openParenthesis=false;
    }
    /* then print the data of node */
    std::cout << node->getValue() << " ";

    if(node->isHighPriorityOperatorNode())
        if(node->getRSon()->isLowPriorityOperatorNode())
        {
            std::cout<<"( ";
            openParenthesis=true;
        }
    /* now recur on right child */
    standardPrintHelper(node->getRSon());

    if(openParenthesis)
    {
        std::cout<<") ";
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
    createFromString(loader.getExpressionString());
    xValue = loader.getXValue();

}

