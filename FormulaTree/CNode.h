#pragma once

#include <string>
#include <vector>
using namespace std;

class CNode {
    //TODO put Getters/Setters
    //private:

public:
    string value;
    vector<CNode*> children;
    CNode(string val);
    //~CNode();


    // Przeciążony operator + dla łatwego łączenia drzew
    CNode* operator+(CNode* other);
};
