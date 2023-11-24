#include "CNode.h"
//#include <iostream>

using namespace std;

CNode::CNode(string val)
{
    value = val;
    left = nullptr;
    right = nullptr;
}

CNode* CNode::operator+(CNode* other) {
    CNode* newNode = new CNode("+");
    newNode->left = this;
    newNode->right = other;
    return newNode;
}

bool CNode::isVariable() const {
    if (value.empty() || !isalpha(value[0]) || isSinCos()) {
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
//TODO make isSinCos
bool CNode::isSinCos() const {
    if (value == "sin" || value == "cos") {
        return true;
    }
    return false;
}
//bool CNode::isSin() const {
//    if (value == "sin") {
//        return true;
//    }
//    return false;
//}
////TODO to delete
//bool CNode::isCos() const {
//    if (value == "cos") {
//        return true;
//    }
//    return false;
//}
//TODO to delete if isClosed enough
//bool CNode::isOccupied() const {
//    if (isNumber() || isVariable()) {
//        return true;
//    }
//
//    if (left == NULL) {
//        return false;
//    }
//    if ((isSin() || isCos()) && left != NULL) {
//        return true;
//    }
//
//    if (left != NULL && right != NULL) {
//        return true;
//    }
//    return false;;
//}
