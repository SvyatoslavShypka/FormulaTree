#include "CTree.h"
#include "CNode.h"
#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream>
//TODO check #include and constants and memory leakage
using namespace std;
//TODO change nullptr on NULL
CTree::CTree()
{
    root = nullptr;
}

CTree::~CTree() {
    deleteTree(root);
}

CNode* CTree::getRoot() const {
    return root;
}

CTree& CTree::operator=(const CTree& other) {
    if (this != &other) {
        deleteTree(root);
        root = copyTree(other.root);
    }
    return *this;
}

// Funkcja do wypisywania drzewa w notacji prefiksowej
void CTree::printTree(CNode* node) {
    if (node) {
        cout << node->value << " ";

        // Print children if any
        if (!node->children.empty()) {
            for (size_t i = 0; i < node->children.size(); ++i) {
                printTree(node->children[i]);
            }
        }
        //cout << " ";
    }
}

// Funkcja do wypisywania drzewa w notacji prefiksowej
void CTree::detailedPrintTree(CNode* node) {
    if (node != nullptr) {
        cout << node->value << endl;
        for (const auto& child : node->children) {
            cout << (child ? "Child is: " + child->value : "Child is null") << endl;
        }
        for (const auto& child : node->children) {
            detailedPrintTree(child);
        }
    }
}

// Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
double CTree::evaluate(CNode* node, const map<string, double>& values) {
    if (node == nullptr) return 0.0;

    if (node->value == "+") {
        double result = 0.0;
        for (const auto& child : node->children) {
            result += evaluate(child, values);
        }
        return result;
    }
    else if (node->value == "-") {
        return evaluate(node->children[0], values) - evaluate(node->children[1], values);
    }
    else if (node->value == "*") {
        double result = 1.0;
        for (const auto& child : node->children) {
            result *= evaluate(child, values);
        }
        return result;
    }
    else if (node->value == "/") {
        return evaluate(node->children[0], values) / evaluate(node->children[1], values);
    }
    else if (node->value == "sin") {
        return sin(evaluate(node->children[0], values));
    }
    else if (node->value == "cos") {
        return cos(evaluate(node->children[0], values));
    }
    if (node->value == "multioperator") {
        double result = 0.0;
        for (const auto& child : node->children) {
            result += evaluate(child, values);
        }
        return result;
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
    //TODO to comment it
    detailedPrintTree(root);
}

CNode* CTree::copyTree(const CNode* source) {
    if (!source) {
        return nullptr;
    }

    CNode* newNode = new CNode(source->value);
    for (const auto& child : source->children) {
        newNode->children.push_back(copyTree(child));
    }
    return newNode;
}

void CTree::deleteTree(CNode* node) {
    if (node) {
        for (const auto& child : node->children) {
            deleteTree(child);
        }
        node->children.clear();  // Usuń dzieci przed usunięciem węzła
        delete node;
    }
    root = nullptr;  // Opcjonalnie ustaw korzeń na nullptr po usunięciu całego drzewa
}

CNode* CTree::parseNode(const string& expression, size_t& offset) {
    //stringstream ss(expression);
    int leftWords = 0;
    
    string value;
    int saveOffset;
    //size_t& zero_offset = offset;
    while (offset < expression.size()) {
        string value2;
        while (offset < expression.size() - 1 && expression[offset] == ' ') {
            offset++; // Skip space
        }
        saveOffset = offset;
        //Collect value until next space
        while (offset < expression.size() && expression[offset] != ' ') {
            value2 += expression[offset++];
        }
        leftWords++;
        cout << value2 << " - " << to_string(leftWords) << endl;
    }
    offset = 1; //TODO change it
    while (offset < expression.size() && expression[offset] != ' ') {
        value += expression[offset++];
    }

    if (leftWords == 0) {
        cout << "incorrect input" << endl;
        return nullptr;
    }
    //CNode* newNode = new CNode(value);
    if (root == nullptr) {
        root = new CNode(value);
        leftWords--;
        cout << "Created node with value: " << value << endl;
    }
    createTree(root, expression, offset, leftWords);

    return root;
}

void CTree::createTree(CNode* currentNode, const string& expression, size_t& offset, int leftWords) {
    //finish recursion
    if (!currentNode) {
        return;
    }
    while (currentNode->isClosed) {
        currentNode = currentNode->previous;
    }

    if (currentNode->isVariable() || currentNode->isNumber()) {
        currentNode->isClosed = true;
        currentNode = currentNode->previous;
    }

    if (currentNode->isOperator() && currentNode->children.size() == 2 && !currentNode->isMultiOperator()) {
        currentNode->isClosed = true;
        currentNode = currentNode->previous;
    }

    while (offset < expression.size()) {
        string value;
        while (offset < expression.size() && expression[offset] == ' ') {
            offset++; // Skip spaces
        }
        //Collect value until next space
        while (offset < expression.size() && expression[offset] != ' ') {
            value += expression[offset++];
        }
        CNode* newNode = new CNode(value);
        while (currentNode->isClosed) {
            currentNode = currentNode->previous;
        }
        leftWords--;
        if (currentNode->isVariable() || currentNode->isNumber()) {
            cout << "incorrect input! There are already two childs. To be corrected: " << endl;
            currentNode = currentNode->previous;
            return;
        }
        else {
            newNode->previous = currentNode;
            currentNode->children.push_back(newNode);
            if (currentNode->isSinCos()) {
                currentNode->isClosed = true;
                createTree(currentNode->previous, expression, offset, leftWords);
            }
            else {
                createTree(newNode, expression, offset, leftWords);
            }
        }
    }
}

// Funkcja zwracająca liczbę zmiennych w drzewie
size_t CTree::numberOfVariablesInTree() const {
    set<string> variables;
    collectVariables(root, variables);
    return variables.size();
}

// Funkcja pomocnicza do rekurencyjnego zbierania unikalnych zmiennych
void CTree::collectVariables(const CNode* node, set<string>& variables) const {
    if (!node) return;

    if (node->isVariable()) {
        variables.insert(node->value);
    }

    for (const auto& child : node->children) {
        collectVariables(child, variables);
    }
}

// Funkcja zwracająca nazwę zmiennej na podstawie indeksu
string CTree::getVariableNameAtIndex(size_t index) const {
    set<string> variables;
    collectVariables(root, variables);

    if (index < variables.size()) {
        auto it = next(variables.begin(), index);
        return *it;
    }
    else {
        // Możesz obsłużyć błąd lub rzucić wyjątek w przypadku nieprawidłowego indeksu
        // W przykładzie używam prostego komunikatu błędu
        cerr << "Error: Index out of range." << endl;
        return "";
    }
}

// Funkcja pomocnicza do łączenia dwóch drzew
CNode* mergeTrees(const CNode* left, const CNode* right) {
    if (!left) return new CNode(right->value);
    if (!right) return new CNode(left->value);

    CNode* newRoot = new CNode(left->value);

    // Łączenie dzieci drzew
    size_t leftSize = left->children.size();
    size_t rightSize = right->children.size();

    for (size_t i = 0; i < max(leftSize, rightSize); ++i) {
        const CNode* leftChild = i < leftSize ? left->children[i] : nullptr;
        const CNode* rightChild = i < rightSize ? right->children[i] : nullptr;

        newRoot->children.push_back(mergeTrees(leftChild, rightChild));
    }

    return newRoot;
}

// Przeciążony operator +=
CTree& CTree::operator+=(const CTree& other) {
    root = mergeTrees(root, other.root);
    return *this;
}
