#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

struct Production {
    char lhs;
    vector<string> rhs;
};

vector<Production> productions;
map<char, vector<string>> newProductions;

// Function to check if a production has direct left recursion
bool hasDirectLeftRecursion(const Production& prod) {
    for (const auto& rule : prod.rhs) {
        if (rule[0] == prod.lhs) return true;
    }
    return false;
}

// Function to remove direct left recursion from a single production
void removeDirectLeftRecursion(Production& prod) {
    vector<string> alpha, beta;
    char lhs = prod.lhs;
    char newNonTerminal = lhs + '\'';

    for (const auto& rule : prod.rhs) {
        if (rule[0] == lhs) {
            alpha.push_back(rule.substr(1) + newNonTerminal);  // alpha part
        } else {
            beta.push_back(rule + newNonTerminal);             // beta part
        }
    }

    if (!alpha.empty()) {
        newProductions[lhs] = beta;
        newProductions[newNonTerminal] = alpha;
        newProductions[newNonTerminal].push_back("ε"); // Add epsilon to handle empty
    } else {
        newProductions[lhs] = prod.rhs;
    }
}

// Function to remove indirect left recursion from a grammar
void removeIndirectLeftRecursion() {
    for (size_t i = 0; i < productions.size(); i++) {
        char Ai = productions[i].lhs;

        for (size_t j = 0; j < i; j++) {
            char Aj = productions[j].lhs;
            vector<string> newRhs;

            for (auto rule : productions[i].rhs) {
                if (rule[0] == Aj) {
                    for (const auto& replacement : newProductions[Aj]) {
                        newRhs.push_back(replacement + rule.substr(1));
                    }
                } else {
                    newRhs.push_back(rule);
                }
            }
            productions[i].rhs = newRhs;
        }

        if (hasDirectLeftRecursion(productions[i])) {
            removeDirectLeftRecursion(productions[i]);
        } else {
            newProductions[Ai] = productions[i].rhs;
        }
    }
}

// Main function
int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;

    // Input productions
    for (int i = 0; i < n; i++) {
        Production p;
        cout << "Enter left-hand side of production " << i + 1 << ": ";
        cin >> p.lhs;
        int rhsCount;
        cout << "Enter the number of right-hand side options for " << p.lhs << ": ";
        cin >> rhsCount;

        for (int j = 0; j < rhsCount; j++) {
            string rhs;
            cout << "Enter production " << j + 1 << " for " << p.lhs << ": ";
            cin >> rhs;
            p.rhs.push_back(rhs);
        }
        productions.push_back(p);
    }

    // Remove indirect left recursion
    removeIndirectLeftRecursion();

    // Display the transformed grammar
    cout << "\nGrammar after removing left recursion:\n";
    for (const auto& prod : newProductions) {
        cout << prod.first << " -> ";
        for (size_t i = 0; i < prod.second.size(); i++) {
            cout << prod.second[i];
            if (i < prod.second.size() - 1) cout << " | ";
        }
        cout << endl;
    }

    return 0;
}