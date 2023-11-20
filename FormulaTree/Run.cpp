#include "CTree.h"
#include "CNode.h"
using namespace std;

// Funkcja pomocnicza do wczytywania wartości zmiennych
void readValues(const std::string& input, std::vector<double>& values) {
    std::istringstream iss(input);
    double value;
    while (iss >> value) {
        values.push_back(value);
    }
}

int main() {
    CTree tree; // Tworzymy drzewo

    std::string command;
    while (true) {
        std::cout << "Enter command: ";
        std::getline(std::cin, command);

        std::istringstream iss(command);
        std::string cmd;
        iss >> cmd;

        if (cmd == "enter") {
            std::string formula;
            std::getline(iss, formula);
            tree.parseExpression(formula);
            std::cout << "Formula: ";
            tree.printTree(tree.getRoot());
            std::cout << std::endl;
        }
        else if (cmd == "vars") {
            // Wypisz zmienne
            // Implementacja zależy od struktury drzewa, można użyć zbioru (std::set) do przechowywania unikalnych zmiennych
        }
        else if (cmd == "print") {
            // Wypisz drzewo w postaci prefiksowej
            std::cout << "Printed tree: ";
            tree.printTree(tree.getRoot());
            std::cout << std::endl;
        }
        else if (cmd == "comp") {
            std::vector<double> values;
            readValues(command.substr(cmd.length()), values);

            // Sprawdź, czy ilość wartości zgadza się z ilością zmiennych w drzewie
            // Jeśli tak, oblicz wartość drzewa dla podanych wartości
            // Wypisz wynik
        }
        else if (cmd == "join") {
            std::string formula;
            std::getline(iss, formula);

            CTree newTree;
            newTree.parseExpression(formula);
            tree += newTree;
        }
        else {
            std::cout << "Unknown command." << std::endl;
        }
    }

    return 0;
}