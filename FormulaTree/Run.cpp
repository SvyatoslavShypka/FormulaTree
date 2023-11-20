#include "CTree.h"
#include "CNode.h"
using namespace std;

int main() {
    CTree c_tree;
    string expression = "+ * 1 2 a";
    c_tree.parseExpression(expression);

    cout << "Parsed expression: ";
    c_tree.printTree(c_tree.getRoot());
    cout << endl;

    //CTree c_sum, c_a, c_b;
    //c_sum = c_a + c_b;

    return 0;
}