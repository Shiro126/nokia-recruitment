//
// Created by shiro on 02.08.19.
//

#include "PrefixExpression.h"
#include <iostream>
#include <InvalidExpressionError.h>

void PrefixExpression::printInStandard() {
    inorderHelper(head);

}

int PrefixExpression::calculate() {
    return calculateHelper(head);
}

int PrefixExpression::createFromString(std::string &basicString,int index, Node* newNode) {
    int shift{};
    while(isspace(basicString[index]))
    {
        ++index;
        ++shift;
    }
    if(isOperator(basicString[index]))
    {
        //TODO: add code for node creation
        newNode->setValue(std::string(1,basicString[index]));

        newNode->setRSon(new Node{});
        newNode ->setLSon(new Node{});
        if(index + 1 >= basicString.length())
            throw InvalidExpressionError("Invalid expression");
        shift += createFromString(basicString,index+1, newNode->getLSon()) ;
        if(shift + index + 1 >= basicString.length())
            throw InvalidExpressionError("Invalid expression");

        shift += createFromString(basicString,index+shift+1, newNode->getRSon());
        return shift+1;
    }
    else if (basicString[index]== 'x')
    {
        newNode->setValue(std::string(1,basicString[index]));
        return ++shift;
    }
    else
    {
        int numEnd = 0;
        while(isdigit(basicString[index + numEnd]))
        {
            ++numEnd;
        }
        newNode->setValue(basicString.substr(index,numEnd));
        return numEnd + shift;
    }
}

bool PrefixExpression::isOperator(char c)
{
    return (c == '+') || (c == '-') || (c == '\\') || (c == '*');
}

void PrefixExpression::print() {
    if(head==nullptr)
        return;
    printPreorder(head);
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

void PrefixExpression::inorderHelper(Node *node) {

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
    inorderHelper(node->getLSon());

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
    inorderHelper(node->getRSon());

    if(openParenthesis)
    {
        std::cout<<") ";
        openParenthesis=false;
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

        if(node->getValue()[0]=='\\')
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

