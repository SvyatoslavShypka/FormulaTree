#include "CTree.h"
#include "CNode.h"
#include <iostream> 
#include <string> 
#include <vector> 
#include <sstream>
using namespace std;

CTree::CTree() : root(nullptr) {}

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
    if (node != nullptr) {
        std::cout << node->value << std::endl;
        std::cout << (node->left ? "Left is: " + node->left->value : "Left is null") << std::endl;
        std::cout << (node->right ? "Right is: " + node->right->value : "Right is null") << std::endl;
        printTree(node->left);
        printTree(node->right);
    }
}

// Funkcja do wyrysowania drzewa
void CTree::drawTree(CNode* node, int offset) {
    int center = 50;
    if (node != nullptr) {
        if (node == root) {
            offset = 0;
            cout << string(center, ' ') << node->value << endl;
        }
        offset += 10;
        cout << string(center - offset, ' ') << node->left->value << string(2 * offset, ' ') << node->right->value;

        drawTree(node->left, offset);
        drawTree(node->right, offset);
    }
    else {
        return;
    }
}

// Funkcja do wyrysowania drzewa
void CTree::detailTree(CNode* node, int count) {
    if (node != nullptr) {
            cout << count << "                       " << node->value << endl;
            cout << node->left->value << "-------------" << node->right->value << endl;
            count++;
            if (node->left != NULL) {
                detailTree(node->left, count);
            }
            if (node->right != NULL) {
                detailTree(node->right, count);
            }
    }
    else {
        return;
    }
}

// Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
double CTree::evaluate(CNode* node, const std::map<std::string, double>& values) {
    if (node == nullptr) return 0.0;

    if (node->value == "+") {
        return evaluate(node->left, values) + evaluate(node->right, values);
    }
    else if (node->value == "-") {
        return evaluate(node->left, values) - evaluate(node->right, values);
    }
    else if (node->value == "*") {
        return evaluate(node->left, values) * evaluate(node->right, values);
    }
    else if (node->value == "/") {
        return evaluate(node->left, values) / evaluate(node->right, values);
    }
    else if (node->value == "sin") {
        return sin(evaluate(node->left, values));
    }
    else if (node->value == "cos") {
        return cos(evaluate(node->left, values));
    }
    else if (values.find(node->value) != values.end()) {
        return values.at(node->value);
    }
    else {
        return stod(node->value);
    }
}

// Funkcja parsująca wyrażenie z notacji prefiksowej
void CTree::parseExpression(const std::string& expression) {
    size_t offset = 0;
    root = parseNode(expression, offset);
    printTree(root);
}

CNode* CTree::copyTree(const CNode* source) {
    if (!source) {
        return nullptr;
    }

    CNode* newNode = new CNode(source->value);
    newNode->left = copyTree(source->left);
    newNode->right = copyTree(source->right);
    return newNode;
}

void CTree::deleteTree(CNode* node) {
    if (node) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}



CNode* CTree::parseNode(const std::string& expression, size_t& offset) {
    //stringstream ss(expression);
    int leftWords = 0;
    
    string value;
    int saveOffset;
    //size_t& zero_offset = offset;
    while (offset < expression.size()) {
        std::string value2;
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
        cout << "Created node with value: " << value << std::endl;
    }
    createTree(root, expression, offset, leftWords);

    return root;
}

void CTree::createTree(CNode* currentNode, const string& expression, size_t& offset, int leftWords) {
    //finish recursion
    if (currentNode == nullptr || leftWords == 0) {
        return;
    }
    while (currentNode->isClosed) {
        currentNode = currentNode->previous;
    }

    if (currentNode->isVariable() || currentNode->isNumber()) {
        currentNode->isClosed = true;
        currentNode = currentNode->previous;
    }

    while (offset < expression.size()) {
        string value;
        while (offset < expression.size() && expression[offset] == ' ') {
            offset++; // Skip space
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
            if (currentNode->left == nullptr) {
                newNode->previous = currentNode;
                currentNode->left = newNode;
                if (currentNode->isCos() || currentNode->isSin()) {
                    currentNode->isClosed = true;
                }
                createTree(currentNode->left, expression, offset, leftWords);
            }
            else if (currentNode->right == nullptr) {
                newNode->previous = currentNode;
                currentNode->right = newNode;
                currentNode->isClosed = true;
                createTree(currentNode->right, expression, offset, leftWords);
            }
            else {
                cout << "incorrect input! There are already two childs. To be corrected: " << endl;
            }
        }
    }
}

// Funkcja zwracająca liczbę zmiennych w drzewie
size_t CTree::numberOfVariablesInTree() const {
    std::set<std::string> variables;
    collectVariables(root, variables);
    return variables.size();
}

/// Funkcja pomocnicza do rekurencyjnego zbierania unikalnych zmiennych
void CTree::collectVariables(const CNode* node, std::set<std::string>& variables) const {
    if (!node) return;

    if (node->isVariable()) {
        variables.insert(node->value);
    }

    collectVariables(node->left, variables);
    collectVariables(node->right, variables);
}


// Funkcja zwracająca nazwę zmiennej na podstawie indeksu
std::string CTree::getVariableNameAtIndex(size_t index) const {
    std::set<std::string> variables;
    collectVariables(root, variables);

    if (index < variables.size()) {
        auto it = std::next(variables.begin(), index);
        return *it;
    }
    else {
        // Możesz obsłużyć błąd lub rzucić wyjątek w przypadku nieprawidłowego indeksu
        // W przykładzie używam prostego komunikatu błędu
        std::cerr << "Error: Index out of range." << std::endl;
        return "";
    }
}

// Funkcja pomocnicza do łączenia dwóch drzew
CNode* mergeTrees(const CNode* left, const CNode* right) {
    if (!left) return new CNode(right->value);
    if (!right) return new CNode(left->value);

    CNode* newRoot = new CNode(left->value);
    newRoot->left = mergeTrees(left->left, right->left);
    newRoot->right = mergeTrees(left->right, right->right);

    return newRoot;
}

// Przeciążony operator +=
CTree& CTree::operator+=(const CTree& other) {
    root = mergeTrees(root, other.root);
    return *this;
}
