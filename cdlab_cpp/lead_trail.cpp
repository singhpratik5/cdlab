#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

struct Production {
    char lhs;
    vector<string> rhs;
};

map<char, set<char>> leading;
map<char, set<char>> trailing;
vector<Production> productions;

void addLeading(char nonTerminal, char symbol) {
    leading[nonTerminal].insert(symbol);
}

void addTrailing(char nonTerminal, char symbol) {
    trailing[nonTerminal].insert(symbol);
}

// Function to calculate leading symbols
void calculateLeading() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& prod : productions) {
            char lhs = prod.lhs;
            for (const auto& rule : prod.rhs) {
                for (size_t i = 0; i < rule.size(); ++i) {
                    char symbol = rule[i];
                    if (isupper(symbol)) {
                        // Non-terminal, add its leading set
                        size_t beforeSize = leading[lhs].size();
                        leading[lhs].insert(leading[symbol].begin(), leading[symbol].end());
                        if (leading[lhs].size() != beforeSize) {
                            changed = true;
                        }
                        // Stop if we reach a non-terminal
                        break;
                    } else {
                        // Terminal, add directly
                        if (leading[lhs].insert(symbol).second) {
                            changed = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

// Function to calculate trailing symbols
void calculateTrailing() {
    bool changed = true;
    while (changed) {
        changed = false;
        for (const auto& prod : productions) {
            char lhs = prod.lhs;
            for (const auto& rule : prod.rhs) {
                for (int i = rule.size() - 1; i >= 0; --i) {
                    char symbol = rule[i];
                    if (isupper(symbol)) {
                        // Non-terminal, add its trailing set
                        size_t beforeSize = trailing[lhs].size();
                        trailing[lhs].insert(trailing[symbol].begin(), trailing[symbol].end());
                        if (trailing[lhs].size() != beforeSize) {
                            changed = true;
                        }
                        // Stop if we reach a non-terminal
                        break;
                    } else {
                        // Terminal, add directly
                        if (trailing[lhs].insert(symbol).second) {
                            changed = true;
                        }
                        break;
                    }
                }
            }
        }
    }
}

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

    // Calculate Leading and Trailing sets
    calculateLeading();
    calculateTrailing();

    // Display Leading sets
    cout << "\nLeading Sets:\n";
    for (const auto& entry : leading) {
        cout << "LEADING(" << entry.first << ") = { ";
        for (auto symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    // Display Trailing sets
    cout << "\nTrailing Sets:\n";
    for (const auto& entry : trailing) {
        cout << "TRAILING(" << entry.first << ") = { ";
        for (auto symbol : entry.second) {
            cout << symbol << " ";
        }
        cout << "}\n";
    }

    return 0;
}
