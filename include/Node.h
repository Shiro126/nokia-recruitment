//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_NODE_H
#define PREFIXNOTATIONPARSER_NODE_H

#include <utility>
#include <string>
#include <memory>

/**
 * Data structure that holds information about numbers or operators
 */
class Node {
private:
    std::unique_ptr<Node> lSon{};
    std::unique_ptr<Node> rSon{};
    std::string value;


    friend class PrefixExpression;


    void setValue(const std::string &valueString);
    /**
     * Checks if node value contains one of allowed operators
     * @return
     */
    bool isOperatorNode();

    /**
     * Checks if node contains one of following operators: '+', '-'
     */
    bool isLowPriorityOperatorNode();

    /**
     * Checks if node contains one of following operators: '*', '/'
     * @return
     */
    bool isHighPriorityOperatorNode();

    bool areSonsValueNodes();
public:


    explicit Node(char i) : value(std::string(1,i)) {
    }

    explicit Node(std::string value) : value(std::move(value)) {
    }

    Node() = default;

    void setRSon(std::unique_ptr<Node> node);

    void setLSon(std::unique_ptr<Node> node);

    const std::string &getValue() const;

    Node *getLSon() const;

    Node *getRSon() const;
};



#endif //PREFIXNOTATIONPARSER_NODE_H
