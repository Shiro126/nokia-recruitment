//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H
#define PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H


#include "Node.h"
#include <string>

class PrefixExpression {
    Node* head{};
    int xValue{};
public:
    int createFromString(std::string &basicString, int index, Node* newNode);

    explicit PrefixExpression(std::string expressionString) : head{new Node{}}
    {



        createFromString(expressionString,0,head);

    }

    void print();


    void printInStandard();

    void inorderHelper(Node *);

    int calculate();

    bool isOperator(char c);

    void printPreorder(Node *node);

    bool needsParenthesis(Node *pNode);

    int calculateHelper(Node *pNode);
};


#endif //PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H
