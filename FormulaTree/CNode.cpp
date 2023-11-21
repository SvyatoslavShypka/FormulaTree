#include "CNode.h"

CNode::CNode(std::string val) : value(val), left(nullptr), right(nullptr) {}

CNode* CNode::operator+(CNode* other) {
    CNode* newNode = new CNode("+");
    newNode->left = this;
    newNode->right = other;
    return newNode;
}


bool CNode::isVariable() const {
    if (value.empty() || !isalpha(value[0])) {
        return false;
    }

    for (char ch : value) {
        if (!isalnum(ch)) {
            return false;
        }
    }

    return true;
}
