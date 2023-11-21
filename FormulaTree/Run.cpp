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
void readValues(std::stringstream& ss, std::vector<double>& values) {
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
        }
        else if (cmd == "print") {
            // Obsługa polecenia "print"
            std::cout << "Tree: ";
            tree.printTree(tree.getRoot());
            std::cout << std::endl;
        }
        else if (cmd == "vars") {
            // Obsługa polecenia "vars"
            std::set<std::string> variables;
            tree.collectVariables(tree.getRoot(), variables);
            std::cout << "Variables: ";
            for (const auto& variable : variables) {
                std::cout << variable << " ";
            }
            std::cout << std::endl;
        }
        else if (cmd == "enter") {
            string formula;
            getline(ss, formula);
            tree.parseExpression(formula);
            cout << "Expression entered and parsed." << endl;
        }
        else {
            // Obsługa innych poleceń...
        }
    }

    return 0;
}
