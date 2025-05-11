#include <iostream>
#include <vector>
#include <string>

using namespace std;

void eliminateLeftRecursion(string nonTerminal, vector<string> &productions) {
    vector<string> alpha;  // Productions of the form A -> Aα
    vector<string> beta;   // Productions of the form A -> β

    // Separate the alpha and beta productions
    for (string production : productions) {
        if (production[0] == nonTerminal[0]) {
            alpha.push_back(production.substr(1));  // Store the α part
        } else {
            beta.push_back(production);  // Store the β part
        }
    }

    // If there is no left recursion, return original productions
    if (alpha.empty()) {
        cout << nonTerminal << " -> ";
        for (int i = 0; i < beta.size(); i++) {
            cout << beta[i];
            if (i != beta.size() - 1) cout << " / ";
        }
        cout << endl;
        return;
    }

    // Generate new non-terminal A'
    string newNonTerminal = nonTerminal + "'";

    // Print the transformed production for A -> βA'
    cout << nonTerminal << " -> ";
    for (int i = 0; i < beta.size(); i++) {
        cout << beta[i] << newNonTerminal;
        if (i != beta.size() - 1) cout << " / ";
    }
    cout << endl;

    // Print the production for A' -> αA' / ∈
    cout << newNonTerminal << " -> ";
    for (int i = 0; i < alpha.size(); i++) {
        cout << alpha[i] << newNonTerminal;
        if (i != alpha.size() - 1)cout << " / ";
    }
    cout << " /#" << endl;  // # represents epsilon (∈)
}

int main() {
    string nonTerminal;
    int numProductions;

    // Input the grammar
    cout << "Enter the non-terminal: ";
    cin >> nonTerminal;

    cout << "Enter the number of productions for " << nonTerminal << ": ";
    cin >> numProductions;

    vector<string> productions(numProductions);
    cout << "Enter the productions (use # for epsilon):" << endl;
    for (int i = 0; i < numProductions; i++) {
        cout << nonTerminal << " -> ";
        cin >> productions[i];
    }

    // Eliminate left recursion
    eliminateLeftRecursion(nonTerminal, productions);

    return 0;
}