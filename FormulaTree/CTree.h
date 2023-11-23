#pragma once

#include <iostream>
#include <map>
#include <set>
using namespace std;

class CNode;

class CTree {
private:
    CNode* root;
    CNode* previous;

    void deleteTree(CNode* node);
    CNode* parseNode(const std::string& expression, size_t& offset);
    CNode* copyTree(const CNode* source);

public:
    CTree();
    ~CTree();

    CNode* getRoot() const;

    CTree& operator=(const CTree& other);

    void createTree(CNode* currentNode, const string& expression, size_t& offset, int leftWords);
    void printTree(CNode* node);
    void drawTree(CNode* node, int offset);
    double evaluate(CNode* node, const std::map<std::string, double>& values);
    void parseExpression(const std::string& expression);

    CTree& operator+=(const CTree& other);
    //friend CTree operator+(const CTree& lhs, const CTree& rhs);

    size_t numberOfVariablesInTree() const;
    void collectVariables(const CNode* node, std::set<std::string>& variables) const;
    std::string getVariableNameAtIndex(size_t index) const;
};
