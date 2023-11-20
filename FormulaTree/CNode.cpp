//#include <iostream>
#include <vector>
//#include <map>
//#include <cmath>
#include <sstream>
using namespace std;

class CNode {
public:
    string value;
    vector<CNode*> children;

    CNode(string val) : value(val) {}

    // Przeciążony operator + dla łatwego łączenia drzew
    CNode* operator+(CNode* other) {
        CNode* newNode = new CNode("+");
        newNode->children.push_back(this);
        newNode->children.push_back(other);
        return newNode;
    }
};