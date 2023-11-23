#pragma once

#include <string>

class CNode {
public:
    std::string value;
    CNode* left;
    CNode* right;

    CNode(std::string val);
    CNode* operator+(CNode* other);
    bool isVariable() const;
    bool isNumber() const;
    bool isOperator() const;
    bool isSin() const;
    bool isCos() const;
};