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

public:
    CNode* copyTree(const CNode* source);
    void deleteTree(CNode* node);
    CTree();
    ~CTree();

    CNode* getRoot() const;

    CTree& operator=(const CTree& other);

    void createTree(CNode* currentNode, const string& expression, size_t& offset);
    void printTree(CNode* node);
    double evaluate(CNode* node, const map<string, double>& values);
    void parseExpression(const string& expression);

    CTree& operator+=(const CTree& other);

    size_t numberOfVariablesInTree() const;
    void collectVariables(const CNode* node, set<string>& variables) const;
    string getVariableNameAtIndex(size_t index) const;
    CNode* mergeTrees(CNode* left, CNode* right);
};
