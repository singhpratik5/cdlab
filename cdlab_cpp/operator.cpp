#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>

using namespace std;

// Grammar rule struct to hold left and right-hand side of the rule
struct Rule {
    char left;
    vector<string> right;
};

// Function to compute leading set for non-terminal
void computeLeading(vector<Rule>& grammar, map<char, set<char>>& leading) {
    bool changed = true;

    while (changed) {
        changed = false;

        for (const Rule& rule : grammar) {
            char lhs = rule.left;

            // Process each production in the RHS
            for (const string& rhs : rule.right) {
                // If the first symbol is terminal, add it to leading set
                if (isalpha(rhs[0])) {
                    if (leading[lhs].insert(rhs[0]).second) {
                        changed = true;
                    }
                } else {
                    // Add the leading set of the first non-terminal symbol
                    for (char c : leading[rhs[0]]) {
                        if (leading[lhs].insert(c).second) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

// Function to compute trailing set for non-terminal
void computeTrailing(vector<Rule>& grammar, map<char, set<char>>& trailing) {
    bool changed = true;

    while (changed) {
        changed = false;

        for (const Rule& rule : grammar) {
            char lhs = rule.left;

            // Process each production in the RHS
            for (const string& rhs : rule.right) {
                // If the last symbol is terminal, add it to trailing set
                if (isalpha(rhs.back())) {
                    if (trailing[lhs].insert(rhs.back()).second) {
                        changed = true;
                    }
                } else {
                    // Add the trailing set of the last non-terminal symbol
                    for (char c : trailing[rhs.back()]) {
                        if (trailing[lhs].insert(c).second) {
                            changed = true;
                        }
                    }
                }
            }
        }
    }
}

// Function to print sets
void printSet(const map<char, set<char>>& s, const string& title) {
    cout << title << ":\n";
    for (const auto& pair : s) {
        cout << pair.first << ": { ";
        for (char c : pair.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }
}

// Function to create operator precedence table
void createOperatorPrecedenceTable(map<char, set<char>>& leading, map<char, set<char>>& trailing, vector<char>& terminals) {
    map<pair<char, char>, char> precedenceTable;

    // Filling precedence table with <, >, or = based on leading and trailing sets
    for (char a : terminals) {
        for (char b : terminals) {
            if (a == b) {
                precedenceTable[{a, b}] = '=';
            } else if (leading[a].count(b)) {
                precedenceTable[{a, b}] = '<';
            } else if (trailing[a].count(b)) {
                precedenceTable[{a, b}] = '>';
            }
        }
    }

    // Printing the precedence table
    cout << "\nOperator Precedence Table:\n";
    cout << "  ";
    for (char b : terminals) {
        cout << b << " ";
    }
    cout << "\n";

    for (char a : terminals) {
        cout << a << " ";
        for (char b : terminals) {
            if (precedenceTable.count({a, b})) {
                cout << precedenceTable[{a, b}] << " ";
            } else {
                cout << "  "; // For empty relations
            }
        }
        cout << "\n";
    }
}

int main() {
    // Define the grammar rules with vector<string> for RHS
    vector<Rule> grammar = {
        {'E', {"E+E", "E*E", "id"}}
    };

    // Define the terminals
    vector<char> terminals = {'+', '*', 'i', '$'}; // 'i' represents "id"

    // Maps to store leading and trailing sets
    map<char, set<char>> leading, trailing;

    // Compute leading and trailing sets
    computeLeading(grammar, leading);
    computeTrailing(grammar, trailing);

    // Print the leading and trailing sets
    printSet(leading, "Leading");
    printSet(trailing, "Trailing");

    createOperatorPrecedenceTable(leading, trailing, terminals);

    return 0;
}
