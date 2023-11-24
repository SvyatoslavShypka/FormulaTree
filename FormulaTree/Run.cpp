#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <sstream>
#include <set>
#include "CNode.h"
#include "CTree.h"

using namespace std;

// Funkcja do wczytywania wartości z stringstream
void readValues(stringstream& ss, vector<double>& values) {
    double value;
    while (ss >> value) {
        values.push_back(value);
    }
}

int main() {
    CTree tree;

    while (true) {
        cout << "Enter command: ";
        string command;
        getline(cin, command);

        stringstream ss(command);
        string cmd;
        ss >> cmd;

        if (cmd == "comp") {
            // Obsługa polecenia "comp"
            // Odczytaj wartości i przypisz do odpowiednich zmiennych w drzewie

            vector<double> values;
            readValues(ss, values);

            // Sprawdź, czy liczba wartości jest zgodna z ilością zmiennych w drzewie
            if (values.size() != tree.numberOfVariablesInTree()) {
                cout << "Error: Incorrect number of values provided for computation." << endl;
            }
            else {
                // Stworzenie mapy zmiennych i ich wartości
                map<string, double> variableValues;
                for (size_t i = 0; i < values.size(); ++i) {
                    variableValues[tree.getVariableNameAtIndex(i)] = values[i];
                }

                // Wywołanie funkcji evaluate na korzeniu drzewa
                double result = tree.evaluate(
                    tree.getRoot(), variableValues);

                // Wyświetlenie wyniku
                cout << "Result: " << result << endl;
            }
        } //TODO make print easy: repeat the formula
        else if (cmd == "print") {
            // Obsługa polecenia "print"
            cout << "Tree: ";
            if (!tree.getRoot()) {
                cout << "Tree doesn't exist" << endl;
            }
            else {
                tree.printTree(tree.getRoot());
                cout << endl;
            }
        }
        else if (cmd == "det") {
            // Obsługa polecenia "print"
            cout << "Tree: ";
            if (!tree.getRoot()) {
                cout << "Tree doesn't exist" << endl;
            }
            else {
                tree.detailedPrintTree(tree.getRoot());
                cout << endl;
            }
        }
        else if (cmd == "vars") {
            // Obsługa polecenia "vars"
            set<string> variables;
            tree.collectVariables(tree.getRoot(), variables);
            cout << "Variables: ";
            for (const auto& variable : variables) {
                cout << variable << " ";
            }
            cout << endl;
        }
        else if (cmd == "enter") {
            string formula;
            getline(ss, formula);
            tree.parseExpression(formula);
            cout << "Expression entered and parsed." << endl;
        } //TODO To correct delete with memory leakage
        else if (cmd == "del") {
            tree.deleteTree(tree.getRoot());
            cout << "Tree was deleted" << endl;
        }
        else if (cmd == "join") {
            CTree newTree;
            string formula;
            getline(ss, formula);
            newTree.parseExpression(formula);
            tree += newTree;
            cout << "Tree was merged" << endl;
        }
        else if (cmd == "exit") {
            cout << "Exit" << endl;
            return 0;
        }
        else { //TODO Delete Tree
            // Obsługa innych poleceń...
        }
    }

    return 0;
}
