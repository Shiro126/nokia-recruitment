//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H
#define PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H


#include "Node.h"
#include "DataLoader.h"
#include <string>
/**
 * @class PrefixExpression
 */
class PrefixExpression {
    /**
     * Pointer to the root of expression tree
     */
    std::unique_ptr<Node> root{};
    /**
     * xValue stores value that needs to be put in place of x
     */
    int xValue{};

    bool x{};

private:
    /**
     * Prints the tree in preorder fashion.
     * @param node -  beginning node.
     */
    void printPreorder(std::ostream& output, Node *node);

    /**
     * Function that calculates the value of expression from given tree point
     * @param pNode starting node
     * @return calculated integer value of expresion
     */
    int calculateHelper(Node *pNode);

    /**
     * Helper function that prints expressions in standard notation from a given node
     * @param output output stream
     * @param node  starting node
     */
    void standardPrintHelper(std::ostream& output,Node *node);

    /**
     *
     * @brief Function that checks if char value is one of valid operators.
     * Valid operators: '+', '-', '/', '*'
     * @param c char to check
     * @return true - c is valid operator, false otherwise
     */
    bool isOperator(char c);

    /**
    * @Brief Function creates expression tree from string
    *
    * Function is used to populate PrefixExpression with data.
    *
    * @param expressionString string that contains expression
    * @param newNode Pointer to the root of the tree
    * @param index  starting index of expression in string
    *
    * @return count how many characters from string were used to create expression
    */
    int createFromStringHelper(const std::string &expressionString, int index, Node *newNode);



    bool simplifyHelper(Node *pNode);

public:

    /**
     * Public function for creating expression tree from string
     * @param expressionString
     */
    void createFromString(const std::string &expressionString);
    /**
     * Constructor for creating expression from string
     * @param expressionString
     */
    explicit PrefixExpression(const std::string &expressionString) : root{new Node{}}
    {
        createFromStringHelper(expressionString, 0, root.get());

    }

    void load(const DataLoader& loader);

    /**
     * Prints expression in prefix notation
     */
    void print(std::ostream& output);

    /**
     * Prints expression in standard notation
     * @param output output stream
     */
    void printInStandard(std::ostream& output);

    /**
     * calculates expression value
     * @return int expression value
     *
     */
    int calculate();
    /**
     * Used to simplify expression
     */
    void simplify();

    bool hasX();

    void setX(int x);

    int getXValue() const;

    PrefixExpression();

};


#endif //PREFIXNOTATIONPARSER_PREFIXEXPRESSION_H
