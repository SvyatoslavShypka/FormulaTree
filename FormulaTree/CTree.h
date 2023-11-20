#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include "CNode.h"
using namespace std;


class CTree {
private:
    CNode* root;

    // Funkcja do usuwania drzewa
    void deleteTree(CNode* node);

    // Funkcja pomocnicza do parsowania wyrażenia
    CNode* parseNode(const string& expression, size_t& offset);

public:
    // Konstruktor
    CTree();

    // Destruktor
    ~CTree();

    //Getters:
    CNode* getRoot() const;

    // Przeciążony operator przypisania
    CTree& operator=(const CTree& other);

    // Funkcja do kopiowania drzewa
    void copyTree(CNode* dest, const CNode* source);

    // Funkcja do wypisywania drzewa w notacji prefiksowej
    void printTree(CNode* node);

    // Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
    double evaluate(CNode* node, const map<std::string, double>& values);

    // Funkcja parsująca wyrażenie z notacji prefiksowej
    void parseExpression(const string& expression);

    // Przeciążony operator +=
    CTree& operator+=(const CTree& other);

    // Przeciążony operator +
    friend CTree operator+(const CTree& lhs, const CTree& rhs);
};