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

    // Funkcja sprawdzająca, czy węzeł reprezentuje zmienną
    bool CNode::isVariable() const {
        if (value.empty() || !isalpha(value[0])) {
            // Wartość jest pusta lub pierwszy znak nie jest literą, więc to nie jest zmienna
            return false;
        }

        for (char ch : value) {
            // Sprawdzamy, czy wszystkie znaki są literami lub cyframi
            if (!isalnum(ch)) {
                // Znak nie jest literą ani cyfrą, więc to nie jest poprawna zmienna
                return false;
            }
        }

        // Wartość zawiera co najmniej jedną literę, co sprawia, że może być zmienną
        return true;
    }
