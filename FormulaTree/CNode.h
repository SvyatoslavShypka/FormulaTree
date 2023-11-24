#pragma once

#include <string>
using namespace std;

class CNode {
public:
    string value;
    CNode* left;
    CNode* right;
    CNode* previous;
    bool isClosed;

    CNode(string val);
    CNode* operator+(CNode* other);
    bool isVariable() const;
    bool isNumber() const;
    bool isOperator() const;
    bool isSinCos() const;
};