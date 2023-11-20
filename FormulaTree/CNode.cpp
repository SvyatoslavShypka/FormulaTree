//#include <iostream>
#include <vector>
//#include <map>
//#include <cmath>
#include <sstream>
#include "CNode.h"
using namespace std;

    CNode::CNode(string val) {
        value = val;
    }

    // Przeciążony operator + dla łatwego łączenia drzew
    CNode* CNode::operator+(CNode* other) {
        CNode* newNode = new CNode("+");
        newNode->children.push_back(this);
        newNode->children.push_back(other);
        return newNode;
    }
