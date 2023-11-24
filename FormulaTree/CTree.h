#pragma once

#include <iostream>
#include <map>
#include <set>
using namespace std;

class CNode;

class CTree {
private:
    CNode* root;

    CNode* parseNode(const string& expression, size_t& offset);
    CNode* copyTree(const CNode* source);

public:
    void deleteTree(CNode* node);
    CTree();
    ~CTree();

    CNode* getRoot() const;

    CTree& operator=(const CTree& other);

    void createTree(CNode* currentNode, const string& expression, size_t& offset, int leftWords);
    void printTree(CNode* node);
    void detailedPrintTree(CNode* node);
    //void drawTree(CNode* node, int offset);
    //void detailTree(CNode* node, int count);
    double evaluate(CNode* node, const map<string, double>& values);
    void parseExpression(const string& expression);

    CTree& operator+=(const CTree& other);
    //friend CTree operator+(const CTree& lhs, const CTree& rhs);

    size_t numberOfVariablesInTree() const;
    void collectVariables(const CNode* node, set<string>& variables) const;
    string getVariableNameAtIndex(size_t index) const;
};
