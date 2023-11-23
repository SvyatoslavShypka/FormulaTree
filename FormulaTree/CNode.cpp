#include "CNode.h"

CNode::CNode(std::string val) : value(val), left(nullptr), right(nullptr) {}

CNode* CNode::operator+(CNode* other) {
    CNode* newNode = new CNode("+");
    newNode->left = this;
    newNode->right = other;
    return newNode;
}


bool CNode::isVariable() const {
    if (value.empty() || !isalpha(value[0] || isSin() || isCos())) {
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

bool CNode::isSin() const {
    if (value == "sin") {
        return true;
    }
    return false;
}

bool CNode::isCos() const {
    if (value == "cos") {
        return true;
    }
    return false;
}
