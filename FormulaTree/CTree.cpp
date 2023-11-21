#include "CTree.h"
#include "CNode.h"
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
        cout << node->value << " ";
        printTree(node->left);
        printTree(node->right);
    }
}

// Funkcja do obliczania wartości wyrażenia dla podanych wartości zmiennych
double CTree::evaluate(CNode* node, const std::map<std::string, double>& values) {
    if (node == nullptr) return 0.0;

    if (node->value == "+") {
        return evaluate(node->left, values) + evaluate(node->right, values);
    }
    else if (node->value == "sin") {
        return sin(evaluate(node->left, values));
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
    std::cout << root->value << std::endl;
    std::cout << (root->left ? "Left exists" : "Left is null") << std::endl;
    std::cout << (root->right ? "Right exists" : "Right is null") << std::endl;
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
    std::string value;
    while (offset < expression.size() && expression[offset] != ' ') {
        value += expression[offset++];
    }

    CNode* newNode = new CNode(value);
    std::cout << "Created node with value: " << value << std::endl;

    // Check for children (subexpressions)
    while (offset < expression.size() && expression[offset] == ' ') {
        offset++; // Skip space
        if (offset < expression.size()) {
            CNode* childNode = parseNode(expression, offset);
            std::cout << "Adding child with value: " << childNode->value << " to parent with value: " << newNode->value << std::endl;

            if (newNode->left == nullptr) {
                newNode->left = childNode;
            }
            else if (newNode->right == nullptr) {
                newNode->right = childNode;
            }
            else {
                // If both left and right are already set, create a new parent node
                CNode* newParent = new CNode("+");
                newParent->left = newNode;
                newParent->right = childNode;
                newNode = newParent;
            }
        }
    }

    return newNode;
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
