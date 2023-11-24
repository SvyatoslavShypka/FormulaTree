#include "CNode.h"
//#include <iostream>

using namespace std;

CNode::CNode(string val)
{
    value = val;
    previous = nullptr;
    isClosed = false;
}

CNode* CNode::operator+(CNode* other) {
    CNode* newNode = new CNode("+");
    newNode->children.push_back(this);
    newNode->children.push_back(other);
    return newNode;
}

bool CNode::isVariable() const {
    if (value.empty() || !isalpha(value[0]) || isSinCos() || isMultiOperator()) {
        return false;
    }

    for (char ch : value) {
        if (!isalnum(ch)) {
            return false;
        }
    }
    return true;
}

bool CNode::isNumber() const {
    for (char ch : value) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

bool CNode::isOperator() const {
    if (value == "+" || value == "-" || value == "*" || value == "/") {
        return true;
    }
    return false;
}

bool CNode::isMultiOperator() const {
    if (value == "multioperator") {
        return true;
    }
    return false;
}
//TODO make isSinCos
bool CNode::isSinCos() const {
    if (value == "sin" || value == "cos") {
        return true;
    }
    return false;
}
