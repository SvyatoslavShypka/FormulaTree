#pragma once

#include <string>
#include <vector>
using namespace std;

class CNode {
public:
    string value;
    vector<CNode*> children;
    CNode* previous;
    bool isClosed;

    CNode(string val);
    CNode* operator+(CNode* other);
    bool isVariable() const;
    bool isNumber() const;
    bool isOperator() const;
    bool isSinCos() const;
    CNode* findLastNode(CNode* node) const;
};

const string index_error = "Error: Index out of range.";
const string full_childs = "incorrect input! There are already two childs";