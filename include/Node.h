//
// Created by shiro on 02.08.19.
//

#ifndef PREFIXNOTATIONPARSER_NODE_H
#define PREFIXNOTATIONPARSER_NODE_H
#include <utility>
#include <string>


class Node {
private:
    Node* lSon{};
    Node* rSon{};
    std::string value;
public:
   /* virtual ~Node() {
        delete lSon;
        delete rSon;
    }*/

   explicit Node(char i) : value(&""[i]) {


   }

public:
    explicit Node(std::string value) : value(std::move(value))
    {

    }
    Node(){}

    Node *getLSon() const {
        return lSon;
    }

    void setLSon(Node *lSon) {
        Node::lSon = lSon;
    }

    Node *getRSon() const {
        return rSon;
    }

    void setRSon(Node *rSon) {
        Node::rSon = rSon;
    }

    const std::string &getValue() const {
        return value;
    }

    void setValue(const std::string &value) {
        Node::value = value;
    }
    bool isOperatorNode()
    {
       return (value[0] == '*') || (value[0] == '\\')
                || (value[0] == '-') || (value[0] == '+');
    }
    bool isLowPriorityOperatorNode()
    {
        return (value[0]=='+') || (value[0]=='-');
    }
    bool isHighPriorityOperatorNode(){
        return (value[0]=='*') || (value[0]=='\\');
   }

};

#endif //PREFIXNOTATIONPARSER_NODE_H
