//
// Created by shiro on 04.08.19.
//

#include "Node.h"
void Node::setLSon(std::unique_ptr<Node> node) {
    lSon = move(node);
}

Node *Node::getLSon() const {
    return lSon.get();
}

Node *Node::getRSon() const {
    return rSon.get();
}

void Node::setRSon(std::unique_ptr<Node> node) {
    Node::rSon = move(node);
}

const std::string &Node::getValue() const {
    return value;
}

void Node::setValue(const std::string &valueString) {
    Node::value = valueString;
}

bool Node::isOperatorNode() {
    return (value[0] == '*') || (value[0] == '\\')
           || (value[0] == '-') || (value[0] == '+');
}

bool Node::isLowPriorityOperatorNode() {
    return (value[0] == '+') || (value[0] == '-');
}

bool Node::isHighPriorityOperatorNode() {
    return (value[0] == '*') || (value[0] == '\\');
}
