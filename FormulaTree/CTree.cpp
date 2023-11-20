#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include "CNode.h"
#include "CTree.h"
using namespace std;

    // Funkcja do usuwania drzewa
    void CTree::deleteTree(CNode* node) {
        if (node != nullptr) {
            for (auto child : node->children) {
                deleteTree(child);
            }
            delete node;
        }
    }

    // Funkcja pomocnicza do parsowania wyrażenia
    CNode* parseNode(const string& expression, size_t& offset) {
        string value;
        while (offset < expression.size() && expression[offset] != ' ') {
            value += expression[offset++];
        }

        CNode* newNode = new CNode(value);

        //Check for children (subexpressions)
        while (offset < expression.size() && expression[offset] == ' ') {
            offset++; // Skip space
            if (offset < expression.size()) {
                newNode->children.push_back(parseNode(expression, offset));
            }
        }

        return newNode;
    }


    // Konstruktor
    CTree::CTree() {
        root = nullptr;
    }

    // Destruktor
    CTree::~CTree() {
        deleteTree(root);
    }

    CNode* CTree::getRoot()
    {
        return root;
    }

    // Przeciążony operator przypisania
    CTree& CTree::operator=(const CTree& other) {
        if (this != &other) {
            deleteTree(root);
            root = new CNode(other.root->value);
            copyTree(root, other.root);
        }
        return *this;
    }
        

    // Funkcja do kopiowania drzewa
    void CTree::copyTree(CNode* dest, const CNode* source) {
        for (const auto child : source->children) {
            CNode* newChild = new CNode(child->value);
            dest->children.push_back(newChild);
            copyTree(newChild, child);
        }
    }

    // Funkcja do wypisywania drzewa w notacji prefiksowej
    void CTree::printTree(CNode* node) {
        if (node != nullptr) {
            cout << node->value << " ";
            for (const auto child : node->children) {
                printTree(child);
            }
        }
    }

    // Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
    double CTree::evaluate(CNode* node, const map<string, double>& values) {
        if (node == nullptr) return 0.0;

        if (node->value == "+") {
            return evaluate(node->children[0], values) + evaluate(node->children[1], values);
        }
        else if (node->value == "sin") {
            return sin(evaluate(node->children[0], values));
        }
        else if (values.find(node->value) != values.end()) {
            return values.at(node->value);
        }
        else {
            return stod(node->value);
        }
    }

    // Funkcja parsująca wyrażenie z notacji prefiksowej
    void CTree::parseExpression(const string& expression) {
        size_t offset = 0;
        root = parseNode(expression, offset);
    }

    //// Przeciążony operator +=
    //CTree& CTree::operator+=(const CTree& other)
    //{
    //    CNode* newRoot = root + other.root;
    //    deleteTree(root);
    //    root = newRoot;
    //    return *this;
    //}

    // Przeciążony operator +
    CTree operator+(const CTree& lhs, const CTree& rhs)
    {
        CTree result;
        //result.root = lhs.root + rhs.root;
        return result;
    }
